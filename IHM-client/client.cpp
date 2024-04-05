//
// Created by ahliko on 30/03/24.
//

#include "client.h"

#include <iostream>
#include <cstring>
#include <thread>
#include <exception>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


void TCPTestClient::SendMessage(const std::string &message) {
    if (socketConnection == -1) {
        return;
    }
    try {
        send(socketConnection, message.c_str(), message.length(), 0);
        std::cout << "Client sent his message - should be received by server" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Socket exception: " << e.what() << std::endl;
    }
}

void TCPTestClient::ListenForData() {
    try {
        struct sockaddr_in serverAddress;
        char buffer[1024] = {0};

        if ((socketConnection = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            throw std::runtime_error("Socket creation error");
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(50051);

        if (inet_pton(AF_INET, "10.33.73.161", &serverAddress.sin_addr) <= 0) {
            throw std::runtime_error("Invalid address/ Address not supported");
        }

        if (connect(socketConnection, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
            throw std::runtime_error("Connection Failed");
        }

        while (true) {
            int bytesRead = read(socketConnection, buffer, 1024);
            if (bytesRead > 0) {
                std::cout << "Server message received as: " << buffer << std::endl;
            }
            std::memset(buffer, 0, sizeof(buffer));
        }
    } catch (const std::exception &e) {
        std::cerr << "Socket exception: " << e.what() << std::endl;
    }
}

void TCPTestClient::ConnectToTcpServer() {
    try {
        clientReceiveThread = std::thread(&TCPTestClient::ListenForData, this);
        clientReceiveThread.detach();
    } catch (const std::exception &e) {
        std::cerr << "On client connect exception: " << e.what() << std::endl;
    }
}

TCPTestClient::TCPTestClient() {
    ConnectToTcpServer();
}
