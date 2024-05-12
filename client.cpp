#include "client.h"

GrpcServiceClient::GrpcServiceClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(GrpcService::NewStub(channel)) {}

std::string GrpcServiceClient::MoveBot(const std::string& dir) {
    MoveBotRequest request;
    request.set_dir(dir);
    MoveBotResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->MoveBot(&context, request, &response);
    if (status.ok()) {
        return response.message();
    } else {
        return "RPC failed";
    }
}

std::string GrpcServiceClient::RotaBot(const std::string& dir) {
    RotaBotRequest request;
    request.set_dir(dir);
    RotaBotResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->RotaBot(&context, request, &response);
    if (status.ok()) {
        return response.message();
    } else {
        return "RPC failed";
    }
}

std::string GrpcServiceClient::InstanceObject(const std::string& object) {
    InstanceObjectRequest request;
    request.set_object(object);
    InstanceObjectResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->InstanceObject(&context, request, &response);
    if (status.ok()) {
        return response.message();
    } else {
        return "RPC failed";
    }
}

std::string GrpcServiceClient::TongsManageMove(const std::string& joinName, int32_t dir) {
    TongsManageMoveRequest request;
    request.set_joinname(joinName);
    request.set_dir(dir);
    TongsManageMoveResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->TongsManageMove(&context, request, &response);
    if (status.ok()) {
        return response.message();
    } else {
        return "RPC failed";
    }
}

std::string GrpcServiceClient::TongsManageOpening(bool move) {
    TongsManageOpeningRequest request;
    request.set_move(move);
    TongsManageOpeningResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->TongsManageOpening(&context, request, &response);
    if (status.ok()) {
        return response.message();
    } else {
        return "RPC failed";
    }
}

std::string GrpcServiceClient::MoveCam(int32_t distance) {
    MoveCamRequest request;
    request.set_distance(distance);
    MoveCamResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->MoveCam(&context, request, &response);
    if (status.ok()) {
        return response.message();
    } else {
        return "RPC failed";
    }
}
