//
// Created by ariel on 7/5/2024.
//

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
         * @breif Client name to be displayed to users.
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
        /*!
         * Create new RegisteredClient instance
         * @param DisplayName The display name of the client.
         * @param Address     Address of the client.
         */
        RegisteredClient(string DisplayName, sockaddr_in Address)
        : ID(count++), DisplayName(move(DisplayName)), IncomingMessages(), Address(Address),
        IsConnected(false), LastActivity(), Friends() {}
        //endregion

        //region Methods
        /**
         * @brief Add a new friend of the client if they are not already friends.
         * @param Client Pointer to the client to add as a friend to self.
         * @return whether a change had occurred.
         */
        bool AddFriend(RegisteredClient *Client){
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
        bool HasFriend(long ID){
            bool flag = false;
            for(int i=0;i<this->Friends.size()&&!flag;flag=(ID==this->Friends[i++]->ID));
            return flag;
        }
        /**
         * Pushes a Message to the client's incoming message buffer (if it doesn't already exist there).
         * @param msg Message to push
         * @return Whether the message was pushed or not.
         */
        bool PushMessage(Message *msg){
            bool flag = false;
            for(int i=0;this->IncomingMessages.size()&&!flag;flag=(msg->ID==this->IncomingMessages.ViewContainer()[i].ID));
            if(!flag)
                this->IncomingMessages.push(*msg);
            return !flag;
        }
        /**
         * Retrieves message at the top of the stack.
         * @return
         */
        Message PopMessage(){
            if(this->IncomingMessages.size()>0) {
                Message outp;
                outp = this->IncomingMessages.front();
                this->IncomingMessages.pop();
                return outp;
            }
            return Message();
        }
        /**
         * Update the LastActivity time to the current.
         */
        void UpdateTime(){
            this->LastActivity=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        }
        //endregion
    private:
        /*!
         * Stores number of created users. Used to assign IDs.
         */
        static int count;
    };
} // Backend