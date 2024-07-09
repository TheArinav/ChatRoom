#ifndef REGISTEREDCLIENT_H
#define REGISTEREDCLIENT_H

#include <string>
#include <stack>
#include <netinet/in.h>
#include <vector>
#include <chrono>
#include "../GeneralTypes/Message.h"
#include "../GeneralTypes/MessageQueue.h"

using std::string;
using std::vector;
using std::move;
using GeneralTypes::Message;
using GeneralTypes::MessageQueue;

namespace Backend {
    class RegisteredClient {
    public:
        //region Properties
        /**
         * Host of this server.
         */
        static RegisteredClient Host;
        /**
         * Logical identifier of client.
         */
        unsigned long ID{};
        /**
         * @brief Client name to be displayed to users.
         */
        string DisplayName;
        /**
         * Socket address.
         */
        sockaddr_in Address{};
        /**
         * Is client currently connected.
         */
        bool IsConnected{};
        /**
         * Time of latest activity by client.
         */
        time_t LastActivity{};
        /**
         * List of pending friend requests.
         */
        vector<RegisteredClient*> PendingFriendRequests;
        //endregion

        //region Constructors/Destructors
        ~RegisteredClient();
        RegisteredClient();
        /*!
         * Create new RegisteredClient instance
         * @param DisplayName The display name of the client.
         * @param Address     Address of the client.
         */
        RegisteredClient(string DisplayName, sockaddr_in Address);
        //endregion

        //region Methods
        /**
         * Update the LastActivity time to the current.
         */
        void UpdateTime();
        //endregion
        /*!
         * Stores number of created users. Used to assign IDs.
         */
        static int count;
    };

} // namespace Backend

#endif // REGISTEREDCLIENT_H
