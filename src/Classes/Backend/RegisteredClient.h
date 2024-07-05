//
// Created by ariel on 7/5/2024.
//

#ifndef CHATROOMSERVER_REGISTEREDCLIENT_H
#define CHATROOMSERVER_REGISTEREDCLIENT_H

#include <string>
#include <stack>
#include <vector>
#include "netinet/in.h"
#include "../GeneralTypes/Message.h"

namespace Backend {
    using std::string;
    using std::stack;
    using std::vector;
    using std::move;
    using GeneralTypes::Message;
    using GeneralTypes::Message;

    namespace Backend {
        class RegisteredClient {
        public:
            //region Properties
            /**
             * Logical identifier of client.
             */
            unsigned long ID;
            /**
             * Client name to be displayed to users.
             */
            string DisplayName;
            /**
             * Incoming messages buffer for this client.
             */
            MessageQueue IncomingMessages;
            /**
             * Socket address.
             */
            sockaddr_in Address;
            /**
             * Is client currently connected.
             */
            bool IsConnected;
            /**
             * Time of latest activity by client.
             */
            time_t LastActivity;
            /**
             * List of freinds.
             */
            vector<RegisteredClient*> Friends;
            //endregion

            //region Constructors/Destructors
            RegisteredClient(long, string, sockaddr_in);
            //endregion
        };
    } // Backend

} // Backend

#endif //CHATROOMSERVER_REGISTEREDCLIENT_H
