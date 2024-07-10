//
// Created by ariel on 7/5/2024.
//

#ifndef CHATROOMSERVER_SERVER_H
#define CHATROOMSERVER_SERVER_H

#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <queue>
#include <mutex>
#include "../GeneralTypes/Message.h"
#include "RegisteredClient.h"
#include "ChatRoomHost.h"
#include "../GeneralTypes/ServerAction.h"
#include "../GeneralTypes/ClientAction.h"

using std::vector;
using std::queue;
using std::mutex;
using GeneralTypes::Message;
using Backend::RegisteredClient;
using Backend::ChatRoomHost;
using GeneralTypes::ServerAction;
using GeneralTypes::ClientAction;

namespace Backend {
    class Server{
    public:
        //region Properties
        /**
         * All messages ever received by this server (including deleted ones)
         */
        vector<Message> Messages;
        /**
         * All clients of this server.
         */
        vector<RegisteredClient> Clients;
        /**
         * All chat rooms of this server.
         */
        vector<ChatRoomHost> Rooms;
        /**
         * Action log for this server.
         */
        vector<ServerAction> Log;
        /**
         * Actions awaiting execution.
         */
        queue<ServerAction> ActionQueue;
        /**
         * Used to ensure the ActionQueue is ThreadSafe.
         */
        mutex ActionQueueMutex;
        /**
         * Used to respond to the clients.
         */
        vector<ClientAction> Responses;
        //endregion

        /**
         * Builds a new server instance.
         */
        Server();
        //region Methods
        /**
         * Starts this server.
         */
        bool Start();
        /**
         * Request a shutdown from the server.
         */
        void SendInterruptSignal();
        /**
         * Enqueue a new action to the server.
         * @param act Action to enqueue.
         * @return whether the action was successfully enqueued.
         */
        bool EnqueueAction(ServerAction *act);
        /**
         * Enact the action at the front of the queue.
         * @return
         */
        bool EnactAction();
        /**
         * Generates a new response to a server action.
         */
        void GenerateResponse(ServerAction *act, bool Success);
        /**
         * Attempts to launch all responses.
         */
        void RollResponses();
        //endregion

    private:
        /**
         * Used to cause the server to end execution.
         */
        bool Shutdown;
    };
} // Backend

#endif //CHATROOMSERVER_SERVER_H
