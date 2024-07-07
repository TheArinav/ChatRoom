//
// Created by IMOE001 on 7/7/2024.
//

#ifndef CHATROOMSERVER_BECKENDCOMMS_H
#define CHATROOMSERVER_BECKENDCOMMS_H

#include "Server.h"

using Backend::Server;

namespace Backend {

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
        bool Setup();
        /**
         * Start the server and listen to the socket.
         * @return
         */
        bool Start();
        /*
         * End execution and close the server permanently.
         */
        bool Stop();
    private:
        /*
         * Set up the socket for starting communication with clients.
         */
        bool BuildSocket();
        /*
         * Attempt to bind the socket.
         */
        sockaddr_in BindSocket();
    };

} // Backend

#endif //CHATROOMSERVER_BECKENDCOMMS_H
