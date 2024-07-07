#include <vector>
#include <queue>
#include <iostream>
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
        //endregion

        /**
         * Builds a new server instance.
         */
        Server(){
            ActionMetaData meta;
            ServerAction build = ServerAction(ActionType::ServerBuilt, &RegisteredClient::Host, meta);
            build.CompleteAction();
            Log.push_back(build);
        }

        //region Methods
        /**
         * Starts this server.
         */
        void Start(){
            ActionMetaData meta;
            ServerAction build = ServerAction(ActionType::ServerStarted, &RegisteredClient::Host, meta);
            build.CompleteAction();
            Log.push_back(build);
            while(!Shutdown){
                if(!EnactAction())
                    std::cout << "[SERVER]:[ERROR]: Action failed";
                else
                    std::cout << "[SERVER]:[INFO]: Action enacted! details:\n" << Log.front().ToString() << "\n";
            }
        }
        /**
         * Request a shutdown from the server.
         */
        void SendInterruptSignal(){
            Shutdown = true;
        }
        /**
         * Enqueue a new action to the server.
         * @param act Action to enqueue.
         */
        void EnqueueAction(ServerAction *act){
            if(ActionQueue.front().ID == act->ID)
                return;
            ActionQueue.push(*act);
        }
        /**
         * Enact the action at the front of the queue.
         * @return
         */
        bool EnactAction(){

        }
        //endregion

    private:
        /**
         * Used to cause the server to end execution.
         */
        bool Shutdown;
    };
}// Backend