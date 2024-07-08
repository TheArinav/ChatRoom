#include <vector>
#include <queue>
#include <iostream>
#include <mutex>
#include "../GeneralTypes/Message.h"
#include "RegisteredClient.h"
#include "ChatRoomHost.h"
#include "../GeneralTypes/ServerAction.h"

using std::vector;
using std::queue;
using std::mutex;
using std::lock_guard;
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
        /**
         * Used to ensure the ActionQueue is ThreadSafe.
         */
        mutex ActionQueueMutex;
        //endregion

        /**
         * Builds a new server instance.
         */
        Server(){
            ServerAction build = ServerAction(ActionType::ServerBuilt, RegisteredClient::Host);
            build.CompleteAction();
            Log.push_back(build);
        }

        //region Methods
        /**
         * Starts this server.
         */
        bool Start(){
            ServerAction build = ServerAction(ActionType::ServerStarted, RegisteredClient::Host);
            build.CompleteAction();
            Log.push_back(build);
            while(!Shutdown){
                if(!EnactAction())
                {
                    std::cout << "[SERVER]:[ERROR]: Action failed";
                    return false;
                }
                else
                    std::cout << "[SERVER]:[INFO]: Action enacted! details:\n" << Log.front().ToString() << "\n";
            }
            return true;
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
            ServerAction act = ActionQueue.front();
            ActionQueue.pop();
            bool flag;

            act.CompleteAction();
            Log.push_back(act);
            return true;
        }
        //endregion

    private:
        /**
         * Used to cause the server to end execution.
         */
        bool Shutdown;
    };
}// Backend