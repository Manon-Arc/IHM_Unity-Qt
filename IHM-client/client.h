#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <thread>

class TCPTestClient {
private:
    int socketConnection{};
    std::thread clientReceiveThread;

public:
    explicit TCPTestClient();

    void ConnectToTcpServer();

    void ListenForData();

    void SendMessage(const std::string &message);
};
