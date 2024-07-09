#include <vector>
#include <queue>
#include <iostream>
#include <mutex>
#include "../GeneralTypes/Message.h"
#include "RegisteredClient.h"
#include "ChatRoomHost.h"
#include "../GeneralTypes/ServerAction.h"
#include "Server.h"

using std::vector;
using std::queue;
using std::mutex;
using std::lock_guard;
using GeneralTypes::Message;
using Backend::RegisteredClient;
using Backend::ChatRoomHost;
using GeneralTypes::ServerAction;
using GeneralTypes::ActionType;


namespace Backend {
        /**
         * Builds a new server instance.
         */
        Server::Server(){
            ServerAction build = ServerAction(ActionType::ServerBuilt, RegisteredClient::Host);
            build.CompleteAction();
            Log.push_back(build);
        }

        //region Methods
        /**
         * Starts this server.
         */
        bool Server::Start(){
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
        void Server::SendInterruptSignal(){
            Shutdown = true;
        }
        /**
         * Enqueue a new action to the server.
         * @param act Action to enqueue.
         */
        bool Server::EnqueueAction(ServerAction *act){
            if(ActionQueue.front().ID == act->ID)
                return false;
            ActionQueue.push(*act);
            return true;
        }
        /**
         * Enact the action at the front of the queue.
         * @return
         */
        bool Server::EnactAction() {
            ServerAction act;
            {
                lock_guard<std::mutex> guard(ActionQueueMutex);
                if (ActionQueue.empty()) {
                    return false;
                }
                act = ActionQueue.front();
                ActionQueue.pop();
            }
            //region Temporary variables
            bool flag=false;
            int index=-1;
            //endregion

            switch (act.Type){
                case ActionType::AddClient:{
                  for(int i=0; i<Clients.size()&&!flag; flag=Clients[i].ID==act.ActionRequester.ID);
                  if(flag)
                      return false;
                  Clients.push_back(act.ActionRequester);
                  break;
                }
                case ActionType::RemoveClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients.erase(Clients.begin()+index);
                    break;
                }
                case ActionType::LoginClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients[index].UpdateTime();
                    Clients[index].IsConnected= true;
                    break;
                }
                case ActionType::LogoutClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients[index].UpdateTime();
                    Clients[index].IsConnected= false;
                    break;
                }
                case ActionType::RenameClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients[index].DisplayName=move(act.Util);
                }

                default:{
                    break;
                }
            }

            act.CompleteAction();

            {
                lock_guard<mutex> guard(ActionQueueMutex);
                Log.push_back(act);
            }

            return true;
        }
        //endregion
}// Backend