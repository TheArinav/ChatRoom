#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <iostream>
#include <arpa/inet.h>
#include "Communications.h"
#include "../../../IO/Terminal.h"

using backend::multi_thread_serv::Communications;
using namespace IO;
using Terminal::OutputSender;
using Terminal::OutputInfo;
using Terminal::OutputSender;
using Terminal::OutputType;

namespace backend::multi_thread_serv {
    void *get_in_addr(struct sockaddr *sa) {
        if (sa->sa_family == AF_INET)
            return &(((struct sockaddr_in *) sa)->sin_addr);
        return &(((struct sockaddr_in6 *) sa)->sin6_addr);
    }

    Communications::Communications() {
        this->ServerFD = 0;
        this->ServerSocket = nullptr;
        this->Running = true;
        this->ClientListen = nullptr;
        Setup();
    }

    Communications::~Communications() {
        Stop();
        if (ListenThread.joinable())
            ListenThread.join();
        close(ServerFD);
        for (auto &curConn: this->ClientConnections)
            close(curConn.SocketFD);
        this->ClientConnections.clear();
        if (ServerSocket != nullptr)
            freeaddrinfo(ServerSocket);

    }

    void Communications::Start(void (*clientListen)(int fileDescriptor)) {
        this->ClientListen = clientListen;
        ListenThread = std::thread(&Communications::Listen, this);
    }

    void Communications::Stop() {
        Running = false;
        shutdown(ServerFD, SHUT_RDWR); // Ensure accept call exits
    }

    void Communications::Setup() {
        ServerSocket = SetAddr();
        if (ServerSocket == nullptr) {
            Terminal::WriteOutput(OutputInfo(OutputSender::SERVER_GENERAL, OutputType::ERROR_CRITICAL),
                                  "Failed to set up address info");
            exit(EXIT_FAILURE);
        }
        CreateSock();
        Bind();
    }

    AddressInfo *Communications::SetAddr() {
        const char *port = "3490";
        AddressInfo hints, *serverInfo;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;    // Use IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
        hints.ai_flags = AI_PASSIVE;    // Fill in my IP for me

        if (getaddrinfo(nullptr, port, &hints, &serverInfo) != 0) {
            perror("getaddrinfo() failed!");
            return nullptr;
        }

        return serverInfo;
    }

    void Communications::CreateSock() {
        AddressInfo *p;
        for (p = ServerSocket; p != nullptr; p = p->ai_next) {
            ServerFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if (ServerFD == -1) {
                perror("socket() failed!");
                continue;
            }

            int yes = 1;
            if (setsockopt(ServerFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                perror("setsockopt() failed!");
                close(ServerFD);
                exit(EXIT_FAILURE);
            }

            break;
        }

        if (p == nullptr) {
            Terminal::WriteOutput(OutputInfo(OutputSender::SERVER_GENERAL, OutputType::ERROR_CRITICAL),
                                  "failed to create socket");
            exit(EXIT_FAILURE);
        }
    }

    void Communications::Bind() {
        AddressInfo *p;
        for (p = ServerSocket; p != nullptr; p = p->ai_next) {
            if (bind(ServerFD, p->ai_addr, p->ai_addrlen) == -1) {
                close(ServerFD);
                perror("bind() failed!");
                continue;
            }

            break;
        }

        if (p == nullptr) {
            Terminal::WriteOutput(OutputInfo(OutputSender::SERVER_GENERAL, OutputType::ERROR_CRITICAL),
                                  "failed to bind");
            exit(EXIT_FAILURE);
        }
    }

    void Communications::Listen() {
        if (listen(ServerFD, 10) == -1) { // 10 is the backlog size
            perror("listen() failed!");
            exit(EXIT_FAILURE);
        }
        Terminal::WriteOutput(OutputInfo(OutputSender::SERVER_GENERAL, OutputType::INFO),
                              "waiting for connections..");

        while (Running) {
            struct sockaddr_storage their_addr{};
            socklen_t sin_size = sizeof their_addr;
            int new_fd = accept(ServerFD, (struct sockaddr *) &their_addr, &sin_size);
            if (new_fd == -1) {
                if (!Running) break; // Check if the loop should exit
                perror("accept() failed!");
                continue;
            }

            char s[INET6_ADDRSTRLEN];
            inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
            stringstream ss;
            ss << "Got connection from " << s << std::endl;
            Terminal::WriteOutput(OutputInfo(OutputSender::SERVER_GENERAL, OutputType::NOTIFICATION),
                                  ss.str());

            // Set up the ClientConnection
            ClientConnection newConn;
            newConn.SocketFD = new_fd;
            memcpy(&newConn.Address, &their_addr, sizeof(their_addr));

            // Assign a ClientID (could be more sophisticated)
            newConn.ClientID = ClientConnections.size() + 1;

            // Create a thread to manage the connection
            newConn.ManagerThread = thread([new_fd, this]() {
                if (ClientListen == nullptr)
                    Terminal::WriteOutput(OutputInfo(OutputSender::SERVER_GENERAL, OutputType::ERROR_CRITICAL),
                                          "Undefined behavior: ClientListen() was identified as nullptr!");
                this->ClientListen(new_fd);
                close(new_fd);
            });

            // Detach the thread to allow it to run independently
            newConn.ManagerThread.detach();

            // Add to the vector of connections
            ClientConnections.push_back(std::move(newConn));
        }
    }
} // namespace backend::multi_thread_serv
