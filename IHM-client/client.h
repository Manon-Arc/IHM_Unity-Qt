#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "movements.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using ::MovementRequest;
using ::MovementResponse;
using ::MovementService;

class MovementClient {
public:
    explicit MovementClient(std::shared_ptr<Channel> channel);

    std::string Move(const std::string& direction, int distance);

private:
    std::unique_ptr<MovementService::Stub> stub_;
};
