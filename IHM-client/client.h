#ifndef GRPC_SERVICE_CLIENT_H
#define GRPC_SERVICE_CLIENT_H

#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "com.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;


class GrpcServiceClient {
public:
    explicit GrpcServiceClient(const std::shared_ptr<Channel>& channel);

    std::string MoveTrans(const std::string& dir, int distance);
    std::string MoveRota(const std::string& dir, int angle);
    std::string InstanceObject(const std::string& object);
    std::string TongsManageMove(const std::string& dir, int distance);
    std::string TongsManageOpening(const std::string& move);
    std::string MoveCam(const std::string& dir, int distance);

private:
    std::unique_ptr<GrpcService::Stub> stub_;
};

#endif // GRPC_SERVICE_CLIENT_H
