#include <experimental/optional>
#include <grpcpp/generic/generic_stub.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <thread>
#include <unordered_map>
#include "absl/types/optional.h"

#define DEBUG(x)                                                        \
  do {                                                                  \
    ::std::cerr << __FILE__ ":" << __LINE__ << ": " << x << ::std::endl; \
  } while (false)

struct Server {
  void Start() {
    grpc::ServerBuilder builder;
    builder.RegisterAsyncGenericService(&service_);
    builder.AddListeningPort("0.0.0.0:0", grpc::InsecureServerCredentials(), &port_);
    cq_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
    worker_ = std::thread(&Server::HandleRpcs, this);
  }

  void Shutdown() {
    stopping_ = true;
    server_->Shutdown();
    cq_->Shutdown();
    worker_.join();
  }

  int Port() const { return port_; }

private:
  struct CallData;
  struct Tag;

  grpc::AsyncGenericService service_;
  std::unique_ptr<grpc::Server> server_;
  std::unique_ptr<grpc::ServerCompletionQueue> cq_;
  int port_;
  std::thread worker_;
  std::unordered_map<CallData*, std::shared_ptr<CallData>> data_;
  std::mutex data_mut_;
  std::atomic_bool stopping_{};

  void HandleRpcs();

  void NewData() {
    if (stopping_) return;
    auto d = std::make_shared<CallData>(*this);
    std::lock_guard<std::mutex> lk(data_mut_);
    data_.emplace(d.get(), std::move(d));
  }

  void Remove(CallData* p) {
    std::lock_guard<std::mutex> lk(data_mut_);
    auto it = data_.find(p);
    if (it != data_.end()) data_.erase(it);
  }
};

struct Server::Tag {
  void* tag;
  bool Done() const { return reinterpret_cast<uintptr_t>(tag)&1; }
  void* MarkDone() const { return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(tag)|1); }
  CallData* AsCallData() const { return reinterpret_cast<CallData*>(reinterpret_cast<uintptr_t>(tag)&~1); }
};

struct Server::CallData {
  CallData(Server& server): responder_(&ctx_), server_(server) {
    Tag tag{this};
    assert(!tag.Done());
    ctx_.AsyncNotifyWhenDone(tag.MarkDone());
    server_.service_.RequestCall(&ctx_, &responder_, server_.cq_.get(), server_.cq_.get(), tag.AsCallData());
  }

  void Proceed() {
    switch (state_) {
    case kCreate:
      server_.NewData();
      state_ = kWrite;
      responder_.Read(&request_, this);
      break;
    case kWrite:
      if (write_count_ < 10) {
        ++write_count_;
        responder_.Write(request_, this);
      } else {
        state_ = kFinish;
        responder_.Finish(grpc::Status::OK, this);
      }
      break;
    case kFinish:
      server_.Remove(this);
      break;
    }
  }

private:
  grpc::GenericServerContext ctx_;
  grpc::GenericServerAsyncReaderWriter responder_;
  Server& server_;
  enum { kCreate, kWrite, kFinish } state_ = kCreate;
  grpc::ByteBuffer request_;
  int write_count_ = 0;
};

void Server::HandleRpcs() {
  NewData();
  for (;;) {
    Tag tag;
    bool ok;
    if (!cq_->Next(&tag.tag, &ok)) break;
    if (!ok || tag.Done()) {
      Remove(tag.AsCallData());
    } else {
      std::shared_ptr<CallData> p;
      {
        std::lock_guard<std::mutex> lk(data_mut_);
        auto it = data_.find(tag.AsCallData());
        if (it == data_.end()) continue;
        p = it->second;
      }
      p->Proceed();
    }
  }
}

struct ClientCallData {
  ClientCallData(grpc::GenericStub& stub, grpc::CompletionQueue* cq, uintptr_t tag)
    : cq_(cq), tag_(reinterpret_cast<void*>(tag)) {
    grpc::Slice s(std::string(1<<20, 'a'));
    request_ = grpc::ByteBuffer(&s, 1);
    ctx_.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(10));
    pipe_ = stub.PrepareCall(&ctx_, "/test", cq_);
    pipe_->StartCall(tag_);
  }

  absl::optional<grpc::Status> Proceed(bool ok) {
    DEBUG((uintptr_t)tag_ << '\t' << state_ << '\t' << ok);
    switch (state_) {
    case kStart:
      if (!ok) return grpc::Status(grpc::UNKNOWN, "channel broken");
      state_ = kRead;
      pipe_->Write(request_, tag_);
      return absl::nullopt;
    case kRead:
      if (ok) {
        pipe_->Read(&response_, tag_);
      } else {
        state_ = kFinish;
        pipe_->Finish(&status_, tag_);
      }
      return absl::nullopt;
    case kFinish:
      return status_;
    }
  }

private:
  grpc::CompletionQueue* cq_;
  void* tag_;
  grpc::ClientContext ctx_;
  std::unique_ptr<grpc::ClientAsyncReaderWriter<grpc::ByteBuffer, grpc::ByteBuffer>> pipe_;
  enum { kStart, kRead, kFinish } state_ = kStart;
  grpc::ByteBuffer request_, response_;
  grpc::Status status_;
};

int main() {
  Server server;
  server.Start();
  DEBUG("Server listening on port " << server.Port());
  grpc::GenericStub stub(grpc::CreateChannel("localhost:" + std::to_string(server.Port()),
                                             grpc::InsecureChannelCredentials()));
  grpc::CompletionQueue cq;
  std::vector<std::unique_ptr<ClientCallData>> calls(10);
  for (unsigned i = 0; i < calls.size(); ++i) {
    calls[i] = absl::make_unique<ClientCallData>(stub, &cq, i);
  }
  int pending = calls.size();
  std::vector<bool> done(calls.size());
  for (;;) {
    void* tag;
    bool ok;
    if (!cq.Next(&tag, &ok)) break;
    int i = reinterpret_cast<uintptr_t>(tag);
    if (auto s = calls[i]->Proceed(ok)) {
      if (!s->ok()) {
        DEBUG(s->error_code() << ' ' << s->error_message());
      }
      if (!done[i]) {
        done[i] = true;
        if (--pending == 0) break;
      }
    }
  }
  server.Shutdown();
  return 0;
}