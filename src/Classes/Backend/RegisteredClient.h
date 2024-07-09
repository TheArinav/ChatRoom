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
         * Incoming messages buffer for this client.
         */
        MessageQueue IncomingMessages;
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
         * List of friends.
         */
        vector<RegisteredClient*> Friends;
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
        bool HasFriend(unsigned long ID);
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
        /**
        * Add a friend request to this client.
        * @param client Requester client
        * @return whether the request was successfully added.
        */
        bool ReceiveRequest(RegisteredClient *client);
        /**
        * Answer a pending friend request.
        * @param index The position of the request in the vector.
        * @param answer To accept, enter 'true'. To reject, enter 'false'.
        */
        void AnswerRequest(int index, bool answer);
        //endregion
        /*!
         * Stores number of created users. Used to assign IDs.
         */
        static int count;
    };

} // namespace Backend

#endif // REGISTEREDCLIENT_H
