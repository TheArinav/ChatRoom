//
// Created by ariel on 7/5/2024.
//
#include <iostream>
#include <string>
#include <stack>
#include <netinet/in.h>
#include <vector>
#include <chrono>

#include "RegisteredClient.h"
#include "../GeneralTypes/Message.h"
#include "../GeneralTypes/MessageQueue.h"

using std::string;
using std::vector;
using std::move;
using GeneralTypes::Message;
using GeneralTypes::MessageQueue;
using Backend::RegisteredClient;

namespace Backend {
    int RegisteredClient::count = 0;

    //region Constructors/Destructors
    RegisteredClient::~RegisteredClient() = default;

    RegisteredClient::RegisteredClient() = default;

    /*!
    * Create new RegisteredClient instance
        * @param DisplayName The display name of the client.
         * @param Address     Address of the client.
         */
    RegisteredClient::RegisteredClient(string DisplayName, sockaddr_in Address)
            : ID(count++), DisplayName(move(DisplayName)), IncomingMessages(), Address(Address),
              IsConnected(false), LastActivity(), Friends() {}
    //endregion

    //region Methods
    /**
     * @brief Add a new friend of the client if they are not already friends.
     * @param Client Pointer to the client to add as a friend to self.
     * @return whether a change had occurred.
     */
    bool RegisteredClient::AddFriend(RegisteredClient *Client) {
        bool flag = HasFriend(Client->ID);
        if (!flag)
            this->Friends.push_back(Client);
        return !flag;
    }

    /**
     * @brief Checks whether client has a friend with the given ID.
     * @param ID ID of a client to check
     * @return whether client has a friend with the given ID.
     */
    bool RegisteredClient::HasFriend(unsigned long ID) {
        bool flag = false;
        for (int i = 0; i < this->Friends.size() && !flag; flag = (ID == this->Friends[i++]->ID));
        return flag;
    }

    /**
     * Pushes a Message to the client's incoming message buffer (if it doesn't already exist there).
     * @param msg Message to push
     * @return Whether the message was pushed or not.
     */
    bool RegisteredClient::PushMessage(Message *msg) {
        bool flag = false;
        for (int i = 0;
             i < IncomingMessages.size() && !flag; flag = (msg->ID == IncomingMessages.ViewContainer()[i].ID));
        if (!flag)
            this->IncomingMessages.push(*msg);
        return !flag;
    }

    /**
     * Retrieves message at the top of the stack.
     * @return
     */
    Message RegisteredClient::PopMessage() {
        if (!IncomingMessages.empty()) {
            Message outp;
            outp = IncomingMessages.front();
            IncomingMessages.pop();
            return outp;
        }
        return {};
    }

    /**
     * Update the LastActivity time to the current.
     */
    void RegisteredClient::UpdateTime() {
        this->LastActivity = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }

    /**
     * Add a friend request to this client.
     * @param client Requester client
     * @return whether the request was successfully added.
     */
    bool RegisteredClient::ReceiveRequest(RegisteredClient *client) {
        bool flag = false;
        for (int i = 0;
             i < PendingFriendRequests.size() && !flag; flag = (PendingFriendRequests[i++]->ID == client->ID));
        if (flag || HasFriend(client->ID))
            return false;
        PendingFriendRequests.push_back(client);
        return true;
    }

    /**
     * Answer a pending friend request.
     * @param index The position of the request in the vector.
     * @param answer To accept, enter 'true'. To reject, enter 'false'.
     */
    void RegisteredClient::AnswerRequest(int index, bool answer) {
        if (index < 0 || index >= PendingFriendRequests.size())
            return;
        RegisteredClient *client = PendingFriendRequests[index];
        PendingFriendRequests.erase(std::next(PendingFriendRequests.begin(), index));
        if (answer)
            Friends.push_back(client);
    }
    //endregion
    RegisteredClient RegisteredClient::Host={};
}