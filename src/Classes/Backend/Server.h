//
// Created by ariel on 7/5/2024.
//

#ifndef CHATROOMSERVER_SERVER_H
#define CHATROOMSERVER_SERVER_H

#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <queue>
#include "../GeneralTypes/Message.h"
#include "RegisteredClient.h"
#include "ChatRoomHost.h"
#include "ServerAction.h"

using std::vector;
using std::queue;
using GeneralTypes::Message;
using Backend::RegisteredClient;
using Backend::ChatRoomHost;
using Backend::ServerAction;

namespace Backend {
    class Server{
    public:
        unsigned long ID;
        vector<Message> Messages;
        vector<RegisteredClient> Clients;
        vector<ChatRoomHost> Rooms;
        queue<ServerAction> ActionQueue;

        Server();

        void Start();
        void EnqueueAction(ServerAction *act);

    private:
        static int count;
    };
} // Backend

#endif //CHATROOMSERVER_SERVER_H
