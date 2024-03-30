//
// Created by ahliko on 30/03/24.
//

#include "client.h"

MovementClient::MovementClient(std::shared_ptr<Channel> channel)
        : stub_(MovementService::NewStub(channel)) {}

std::string MovementClient::Move(const std::string &direction, int distance) {
    MovementRequest request;
    request.set_direction(direction);
    request.set_distance(distance);
    MovementResponse response;
    ClientContext context;

    Status status = stub_->Move(&context, request, &response);

    if (status.ok()) {
        return response.message();
    } else {
        std::cout << "RPC failed: " << status.error_message() << std::endl;
        return "RPC failed";
    }
}