#ifndef BACKEND_COMMS_H
#define BACKEND_COMMS_H

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

using std::string;
using std::thread;
using std::unique_ptr;
using Backend::Server;
using std::mutex;
using std::lock_guard;
using std::make_unique;

namespace Backend {
    class BackendComms {
    public:
        /**
         * The Host server.
         */
        static unique_ptr<Server> HostServer;

        /**
         * Sets up socket.
         * @return Whether the setup was completed successfully.
         */
        static bool Setup();

        /**
         * Start the server and listen to the socket.
         * @return
         */
        static bool Start();

        /**
         * End execution and close the server permanently.
         */
        static bool Stop();

    private:
        // Prevent instantiation by making the constructor and destructor private
        BackendComms() = delete;
        ~BackendComms() = delete;
        BackendComms(const BackendComms&) = delete;
        BackendComms& operator=(const BackendComms&) = delete;

        /**
         * Server file descriptor.
         */
        static int server_fd;

        /**
         * Server socket address.
         */
        static sockaddr_in ServerSocket;

        /**
         * Used to ensure stopListen is ThreadSafe.
         */
        static mutex slMutex;

        /**
         * Used to stop the socket listener.
         */
        static bool stopListen;

        /*
         * Set up the socket for starting communication with clients.
         */
        static bool BuildSocket();

        /*
         * Attempt to bind the socket.
         */
        static sockaddr_in BindSocket();

        /**
         * Main loop for receiving instructions from clients.
         */
        static void handleIncomingConnections();
    };

    // Static member definitions
    unique_ptr<Server> BackendComms::HostServer = nullptr;
    int BackendComms::server_fd = 0;
    sockaddr_in BackendComms::ServerSocket = {};
    mutex BackendComms::slMutex;
    bool BackendComms::stopListen = true;

} // namespace Backend

#endif // BACKEND_COMMS_H
