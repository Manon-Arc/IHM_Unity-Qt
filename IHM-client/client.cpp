#include "client.h"

GrpcServiceClient::GrpcServiceClient(const std::shared_ptr<Channel> &channel)
        : stub_(GrpcService::NewStub(channel)) {}

std::string GrpcServiceClient::MoveTrans(const std::string &dir, int distance) {
    MoveTransRequest request;
    MoveTransResponse response;
    ClientContext context;

    request.set_dir(dir);
    request.set_distance(distance);

    Status status = stub_->MoveTrans(&context, request, &response);

    if (status.ok()) {
        return response.message();
    } else {
        std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string GrpcServiceClient::MoveRota(const std::string &dir, int angle) {
    MoveRotaRequest request;
    MoveRotaResponse response;
    ClientContext context;

    request.set_dir(dir);
    request.set_angle(angle);

    Status status = stub_->MoveRota(&context, request, &response);

    if (status.ok()) {
        return response.message();
    } else {
        std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string GrpcServiceClient::InstanceObject(const std::string &object) {
    InstanceObjectRequest request;
    InstanceObjectResponse response;
    ClientContext context;

    request.set_object(object);

    Status status = stub_->InstanceObject(&context, request, &response);

    if (status.ok()) {
        return response.message();
    } else {
        std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string GrpcServiceClient::TongsManageMove(const int joinId, const bool dir) {
    TongsManageMoveRequest request;
    TongsManageMoveResponse response;
    ClientContext context;

    request.set_joinid(joinId);
    request.set_dir(dir);

    Status status = stub_->TongsManageMove(&context, request, &response);

    if (status.ok()) {
        return response.message();
    } else {
        std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string GrpcServiceClient::TongsManageOpening(const bool &move) {
    TongsManageOpeningRequest request;
    TongsManageOpeningResponse response;
    ClientContext context;

    request.set_move(move);

    Status status = stub_->TongsManageOpening(&context, request, &response);

    if (status.ok()) {
        return response.message();
    } else {
        std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string GrpcServiceClient::MoveCam(int distance) {
    MoveCamRequest request;
    MoveCamResponse response;
    ClientContext context;

    request.set_distance(distance);

    Status status = stub_->MoveCam(&context, request, &response);

    if (status.ok()) {
        return response.message();
    } else {
        std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}
