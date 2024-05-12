#ifndef GRPC_SERVICE_CLIENT_H
#define GRPC_SERVICE_CLIENT_H

#include <memory>
#include <grpcpp/grpcpp.h>
#include "com.grpc.pb.h"

class GrpcServiceClient {
public:
    GrpcServiceClient(std::shared_ptr<grpc::Channel> channel);

    std::string MoveBot(const std::string& dir);
    std::string RotaBot(const std::string& dir);
    std::string InstanceObject(const std::string& object);
    std::string TongsManageMove(const std::string& joinName, int32_t dir);
    std::string TongsManageOpening(bool move);
    std::string MoveCam(int32_t distance);

private:
    std::unique_ptr<GrpcService::Stub> stub_;
};

#endif /* GRPC_SERVICE_CLIENT_H */
