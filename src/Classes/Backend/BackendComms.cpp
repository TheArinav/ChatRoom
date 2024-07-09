#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <mutex>
#include <memory>
#include <thread>
#include "Server.h"
#include "../GeneralTypes/ServerAction.h"
#include "RegisteredClient.h"
#include "BackendComms.h"

using std::string;
using std::thread;
using std::unique_ptr;
using std::mutex;
using std::lock_guard;
using std::make_unique;
using Backend::Server;
using Backend::RegisteredClient;
using GeneralTypes::ServerAction;
using Backend::BackendComms;

namespace Backend {
    bool BackendComms::Setup() {
        bool flag;
        sockaddr_in socket{};
        flag = BuildSocket();
        if (!flag) {
            return false;
        }
        socket = BindSocket();
        ServerSocket = socket;
        RegisteredClient HostClient = RegisteredClient("HOST", ServerSocket);
        RegisteredClient::Host = HostClient;
        HostServer = make_unique<Server>();
        return flag;
    }
    bool BackendComms::Start() {
        if (server_fd == 0) {
            return false;
        }
        if (listen(server_fd, 3) < 0) {
            std::cerr << "Listen failed" << std::endl;
            close(server_fd);
            return false;
        }
        {
            lock_guard<mutex> guard(slMutex);
            stopListen = false;
        }
        std::thread listenerThread(handleIncomingConnections);
        listenerThread.detach();
        return HostServer->Start();
    }
    bool BackendComms::Stop() {
        {
            lock_guard<mutex> guard(slMutex);
            stopListen = true;
        }
        close(server_fd);
        return true;
    }
    bool BackendComms::BuildSocket() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == 0) {
            std::cerr << "Socket creation failed" << std::endl;
            return false;
        }
        int opt = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
            close(server_fd);
            return false;
        }
        return true;
    }
    sockaddr_in BackendComms::BindSocket() {
        sockaddr_in addressIn{};
        addressIn.sin_family = AF_INET;
        addressIn.sin_addr.s_addr = INADDR_ANY;
        addressIn.sin_port = htons(8080);
        if (bind(server_fd, (struct sockaddr *)&addressIn, sizeof(addressIn)) < 0) {
            std::cerr << "Bind failed" << std::endl;
            close(server_fd);
            throw std::runtime_error("Bind failed");
        }
        return addressIn;
    }
    void BackendComms::handleIncomingConnections() {
        while (true) {
            {
                lock_guard <mutex> guard(slMutex);
                if (stopListen) {
                    break;
                }
            }
            int addressLen = sizeof(ServerSocket);
            int new_socket = accept(server_fd, (struct sockaddr *) &ServerSocket, (socklen_t * ) & addressLen);
            if (new_socket < 0) {
                std::cerr << "Accept failed" << std::endl;
                continue; // Handle the next connection
            }
            std::thread([new_socket]() {
                char buffer[1024] = {0};
                ssize_t valread = read(new_socket, buffer, 1024);
                if (valread < 0) {
                    std::cerr << "Read failed" << std::endl;
                    close(new_socket);
                    return;
                }
                std::string data(buffer, valread);
                ServerAction action = ServerAction::Deserialize(data);
                {
                    lock_guard <mutex> guard(HostServer->ActionQueueMutex);
                    HostServer->ActionQueue.push(action);
                }
                std::cout << "Received action: " << action.ToString() << std::endl;
                close(new_socket);
            }).detach();
        }
    }

} // namespace Backend
