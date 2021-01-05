#include <iostream>
#include <string>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include "examples/protos/test.grpc.pb.h"

class StreamServiceImpl final : public StreamService::Service
{
  public:
    grpc::Status OpenStream(grpc::ServerContext* context,
                            const OpenStreamRequest* clientMessage,
                            grpc::ServerWriter<MessageToStream>* writer) override
    {
        std::cout << "OpenStream() entered." << std::endl;
        while (!context->IsCancelled())
        {
            size_t waitSec = 5;
            std::cout << "ServerContext not cancelled. Sleeping for " << waitSec << " seconds." << std::endl;
            sleep(waitSec);
        }
        std::cout << "OpenStream() exiting." << std::endl;
        return grpc::Status::CANCELLED;
    }
};

class StreamServer
{
  public:
    StreamServer()
    {
        std::string server_address("0.0.0.0:50051");
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, 2000);
        builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 0);
        builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
        builder.RegisterService(&streamService);
        server = builder.BuildAndStart();
    }
    ~StreamServer()
    {
        server->Shutdown();
    }
  private:
    StreamServiceImpl streamService;
    std::unique_ptr<grpc::Server> server;
};

int main(int argc, char** argv)
{
      StreamServer server;
      std::string notUsed;
      std::cout << "Press Enter to exit." << std::endl;
      std::getline(std::cin, notUsed);
      std::cout << "Enter pressed. Exitting." << std::endl;
      return 0;
}