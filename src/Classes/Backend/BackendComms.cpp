#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <mutex>
#include <memory>
#include <thread>
#include <utility>
#include "Server.h"
#include "../GeneralTypes/ServerAction.h"
#include "RegisteredClient.h"
#include "BackendComms.h"
#include "../../IO/Terminal.h"
#include "MultiThreadedEnvironment/Communications.h"

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
using namespace backend::multi_thread_serv;

using namespace IO;
using Terminal::OutputSender;
using Terminal::OutputInfo;
using Terminal::OutputSender;
using Terminal::OutputType;

namespace Backend {
    class UnimplementedException : public std::exception {
    public:
        explicit UnimplementedException(std::string message = "Feature not implemented")
                : message_(std::move(message)) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message_.c_str();
        }

    private:
        std::string message_;
    };

    unique_ptr<Server> BackendComms::HostServer = nullptr;
    unique_ptr<backend::multi_thread_serv::Communications> BackendComms::MTCommsO = nullptr;
    int BackendComms::server_fd = 0;
    sockaddr_in BackendComms::ServerSocket = {};
    mutex BackendComms::slMutex;
    bool BackendComms::stopListen = true;
    HandleType BackendComms::Handle = HandleType::UNDEFINED;

    bool BackendComms::Setup(HandleType hType) {
        if (hType == HandleType::UNDEFINED) {
            Terminal::WriteOutput(OutputInfo(OutputSender::SERVER_GENERAL, OutputType::ERROR_CRITICAL),
                                  "UNDEFINED is not a valid handle type!");
            return false;
        }
        switch (hType) {
            case HandleType::MultiThread: {
                MTCommsO = std::make_unique<backend::multi_thread_serv::Communications>();
                server_fd = MTCommsO->ServerFD;
                ServerSocket = MTCommsO->ServerSocket;
                break;
            }
            case HandleType::Select: {
                throw UnimplementedException("Select handle is not yet implemented!");
                break;
            }
            case HandleType::Epoll: {
                throw UnimplementedException("Epoll handle is not yet implemented!");
                break;
            }
            default: {
                break;
            }
        }
        Handle = hType;
        return true;
    }

    bool BackendComms::Start() {
        {
            lock_guard<mutex> guard(slMutex);
            stopListen = false;
        }
        switch (Handle) {
            case HandleType::MultiThread: {
                MTCommsO->Start(handleClientConnection);
                break;
            }
            case HandleType::Select: {
                throw UnimplementedException("Select handle is not yet implemented!");
                break;
            }
            case HandleType::Epoll: {
                throw UnimplementedException("Epoll handle is not yet implemented!");
                break;
            }
            default: {
                break;
            }
        }
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

    void BackendComms::handleClientConnection(int fd) {
//        while (true) {
//            {
//                lock_guard<mutex> guard(slMutex);
//                if (stopListen) {
//                    break;
//                }
//            }
//            int addressLen = sizeof(ServerSocket);
//            int new_socket = accept(server_fd, (struct sockaddr *) &ServerSocket, (socklen_t * ) & addressLen);
//            if (new_socket < 0) {
//                std::cerr << "Accept failed" << std::endl;
//                continue; // Handle the next connection
//            }
//            std::thread([new_socket]() {
//                char buffer[1024] = {0};
//                ssize_t valread = read(new_socket, buffer, 1024);
//                if (valread < 0) {
//                    std::cerr << "Read failed" << std::endl;
//                    close(new_socket);
//                    return;
//                }
//                std::string data(buffer, valread);
//                ServerAction action = ServerAction::Deserialize(data);
//                {
//                    lock_guard<mutex> guard(HostServer->ActionQueueMutex);
//                    HostServer->ActionQueue.push(action);
//                }
//                close(new_socket);
//            }).detach();
    }
} // namespace Backend
