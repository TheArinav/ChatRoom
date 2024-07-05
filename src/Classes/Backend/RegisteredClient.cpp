//
// Created by ariel on 7/5/2024.
//

#include <string>
#include <stack>
#include <netinet/in.h>
#include <vector>

#include "../GeneralTypes/Message.h"

using std::string;
using std::stack;
using std::vector;
using GeneralTypes::Message;

namespace Backend {
    class RegisteredClient {
    public:
        //region Properties
        /**
         * Logical identifier of client.
         */
        long ID;
        /**
         * Client name to be displayed to users.
         */
        string DisplayName;
        /**
         * Incoming messages buffer for this client.
         */
        stack<Message> IncomingMessages;
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

        //endregion
    };
} // Backend