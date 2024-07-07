#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include "Server.h"

typedef sockaddr_in SocketAddressIn;
typedef std::string string;
using Backend::Server;

namespace Backend {
    int server_fd;
    sockaddr_in ServerSocket;
    class BeckendComms {
    public:
        /**
         * The Host server.
         */
        Server HostServer;
        /**
         * Sets up socket.
         * @return Whether the setup was completed successfully.
         */
        bool Setup(){
            bool flag;
            sockaddr_in socket;
            flag=BuildSocket();
            socket=BindSocket();
            ServerSocket=socket;
            RegisteredClient HostClient = RegisteredClient("HOST",ServerSocket);
            RegisteredClient::Host=HostClient;
            HostServer=Server();
            return flag;
        }
        /**
         * Start the server and listen to the socket.
         * @return
         */
        bool Start(){
            if(server_fd==0)
                return false;
            if (!HostServer.Start())
                return false;
            if (listen(server_fd, 3) < 0) {
                std::cerr << "Listen failed" << std::endl;
                close(server_fd);
                return false;
            }

            int addressLen = sizeof(ServerSocket);
            int new_socket = accept(server_fd, (struct sockaddr *)&ServerSocket, (socklen_t*)&addressLen);
            if (new_socket < 0) {
                std::cerr << "Accept failed" << std::endl;
                close(server_fd);
                return false;
            }
        }
        /*
         * End execution and close the server permanently.
         */
        bool Stop();
    private:
        /*
         * Set up the socket for starting communication with clients.
         */
        bool BuildSocket(){
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
        /*
         * Attempt to bind the socket.
         */
        sockaddr_in BindSocket(){
            SocketAddressIn addressIn;
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
    };

} // Backend