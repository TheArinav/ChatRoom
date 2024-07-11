//
// Created by IMOE001 on 7/9/2024.
//

#ifndef CHATROOMSERVER_ACCOUNT_H
#define CHATROOMSERVER_ACCOUNT_H

#include <vector>
#include <tuple>
#include <string>
#include <netinet/in.h>
#include "../GeneralTypes/Message.h"
#include "../GeneralTypes/MessageQueue.h"

using std::vector;
using std::tuple;
using std::string;
using GeneralTypes::Message;
using GeneralTypes::MessageQueue;

namespace Frontend {
    class Account {
    public:
        //region Properties
        /**
         * The logical address of the backend client.
         */
        unsigned long long ClientID;
        /**
         * Account display name.
         */
        string DisplayName;
        /**
         * List of friends.
         */
        vector<tuple<unsigned long long,string>> Friends;
        /**
         * List of rooms.
         */
        vector<tuple<unsigned long long,string>> Rooms;
        /**
         * Outgoing message queue.
         */
        MessageQueue OutgoingMessages;
        /**
         * Queue for ingoing messages.
         */
        MessageQueue IngoingMessages;
        /*
         * Registered address.
         */
        sockaddr_in Address;
        //endregion
        //region Constructor
        Account();
        Account(unsigned long long id, string displayName, sockaddr_in addr);
        ~Account();
        //endregion
        //region Methods
        /**
         * Login to a server;
         * @param serverAddress address of requested server.
         */
        void Login(sockaddr_in serverAddress);
        /**
         * Logout from current server.
         */
        void Logout();
        //endregion
    private:
        /**
         * Log a server response.
         * @param msg response to log.
         */
        void Log(string msg);
    };

} // Frontend

#endif //CHATROOMSERVER_ACCOUNT_H
