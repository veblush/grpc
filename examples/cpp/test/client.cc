#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include "examples/protos/test.grpc.pb.h"

class Client
{
  public:
    Client()
    {
        grpc::ChannelArguments channelArgs;
        // There is no need to specify custom keepalive for this test.
        //channelArgs.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 1000);
        //channelArgs.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 3000);
        //channelArgs.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

        std::shared_ptr<grpc::Channel> chan = grpc::CreateCustomChannel(
            "0.0.0.0:50051",
            grpc::InsecureChannelCredentials(),
            channelArgs);

        streamServiceStub = StreamService::NewStub(chan);
    }

    void openStream()
    {
        grpc::ClientContext context;
        OpenStreamRequest messageFromClient;
        std::cout << "gRPC client sending message: " << messageFromClient.DebugString() << std::endl;
        reader = streamServiceStub->OpenStream(&context, messageFromClient);
        if (!reader)
        {
            std::cout << "Failed to create a reader." << std::endl;
            return;
        }

        // If this line is commented out, then the server sometimes does not return from its OpenStream().
        //sleep(1);

        // If TryCancel() is commented out in addition to the sleep(1), the server's OpenStream() returns normally due
        // to the keepalive not getting a response back in 0 milliseconds. This is expected.
        //
        // If TryCancel() is issued right after calling OpenStream() (i.e. without the sleep(1) above), AND if the
        // server's OpenStream() is entered (meaning the TryCancel() signal reached the server later than server's
        // OpenStream() execution), then the server's keepalive system becomes ineffective for some reason. Due to
        // the ineffective keepalive, the server's OpenStream() does not return. THIS IS NOT EXPECTED.
        // If the TryCancel() signal reaches the server before the server executes its OpenStream(), then there is no
        // problem.
        context.TryCancel();
        std::cout << "TryCancel() issued." << std::endl;

        MessageToStream messageToStream;
        if (reader->Read(&messageToStream))
        {
            std::cout << "Error: Not supposed to read any message." << std::endl;
            return;
        }

        std::cout << "Calling Finish()." << std::endl;
        grpc::Status status = reader->Finish();
        if (status.ok())
        {
            std::cout << "Error: Not supposed to receive OK." << std::endl;
            return;
        }
        std::cout << "Stream cancelled successfully." << std::endl;
    }

  private:
    std::unique_ptr<StreamService::Stub> streamServiceStub;
    std::unique_ptr<grpc::ClientReader<MessageToStream>> reader;
};

int main(int argc, char** argv)
{
      Client client;
      client.openStream();
      return 0;
}