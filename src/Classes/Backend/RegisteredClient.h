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
         * Logical identifier of client.
         */
        unsigned long ID;
        /**
         * @brief Client name to be displayed to users.
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
         * List of friends.
         */
        vector<RegisteredClient*> Friends;
        //endregion

        //region Constructors/Destructors
        /*!
         * Create new RegisteredClient instance
         * @param DisplayName The display name of the client.
         * @param Address     Address of the client.
         */
        RegisteredClient(string DisplayName, sockaddr_in Address);

        // Default destructor
        ~RegisteredClient() = default;
        //endregion

        //region Methods
        /**
         * @brief Add a new friend of the client if they are not already friends.
         * @param Client Pointer to the client to add as a friend to self.
         * @return whether a change had occurred.
         */
        bool AddFriend(RegisteredClient *Client);

        /**
         * @brief Checks whether client has a friend with the given ID.
         * @param ID ID of a client to check
         * @return whether client has a friend with the given ID.
         */
        bool HasFriend(long ID);

        /**
         * Pushes a Message to the client's incoming message buffer (if it doesn't already exist there).
         * @param msg Message to push
         * @return Whether the message was pushed or not.
         */
        bool PushMessage(Message *msg);

        /**
         * Retrieves message at the top of the stack.
         * @return Message object from the top of the stack.
         */
        Message PopMessage();

        /**
         * Update the LastActivity time to the current.
         */
        void UpdateTime();
        //endregion

    private:
        /*!
         * Stores number of created users. Used to assign IDs.
         */
        static int count;
    };

} // namespace Backend

#endif // REGISTEREDCLIENT_H
