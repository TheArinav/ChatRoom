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
#include "MultiThreadedEnvironment/Communications.h"

using std::string;
using std::thread;
using std::unique_ptr;
using Backend::Server;
using std::mutex;
using std::lock_guard;
using std::make_unique;

namespace Backend {
    enum class HandleType {
        UNDEFINED,
        MultiThread,
        Select,
        Epoll
    };
    typedef addrinfo AddressInfo;

    class BackendComms {
    public:
        /**
         * Saves the Communications manager object.
         */
        static std::unique_ptr<backend::multi_thread_serv::Communications> MTCommsO;
        /**
         * The Host server.
         */
        static unique_ptr <Server> HostServer;

        /**
         * Sets up socket.
         * @return Whether the setup was completed successfully.
         */
        static bool Setup(HandleType hType);

        /**
         * Start the server and listen to the socket.
         * @return
         */
        static bool Start();

        /**
         * End execution and close the server permanently.
         */
        static bool Stop();

        // Prevent instantiation by making the constructor and destructor private
        BackendComms() = delete;

        ~BackendComms() = delete;

        BackendComms(const BackendComms &) = delete;

        BackendComms &operator=(const BackendComms &) = delete;

    private:
        /**
         * Server file descriptor.
         */
        static int server_fd;

        /**
         * Server socket address.
         */
        static AddressInfo *ServerSocket;

        /**
         * Used to ensure stopListen is ThreadSafe.
         */
        static mutex slMutex;

        /**
         * Used to stop the socket listener.
         */
        static bool stopListen;
        /**
         * Defines the ClientHandle algorithm.
         */
        static HandleType Handle;
        /**
        * Client behavior
        */
        static void handleClientConnection(int fd);
    };

} // namespace Backend

#endif // BACKEND_COMMS_H
