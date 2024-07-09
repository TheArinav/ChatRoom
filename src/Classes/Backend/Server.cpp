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
            {
                ActionQueue.push(*act);
            }
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

            //region Verify Identity
            int reqInd=-1;
            for(int i=0; i<Clients.size() && !(reqInd+1); reqInd=(Clients[i].ID==act.ActionRequester.ID));
            if(Clients[reqInd].Address.sin_addr.s_addr!=act.ActionRequester.Address.sin_addr.s_addr){
                std::cout << "[SERVER]:[WARNING]: Attempted impersonation detected! By client with address:n\n\t"
                << act.ActionRequester.Address.sin_addr.s_addr;
                return false;
            }
            //endregion


            //region Temporary variables
            bool flag=false;
            int index=-1;
            //endregion

            switch (act.Type){
                case ActionType::AddClient:{
                  for(int i=0; i<Clients.size()&&!flag; flag=Clients[i++].ID==act.ActionRequester.ID);
                  if(flag)
                      return false;
                  Clients.push_back(act.ActionRequester);
                  break;
                }
                case ActionType::RemoveClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i++].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients.erase(Clients.begin()+index);
                    break;
                }
                case ActionType::LoginClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i++].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients[index].UpdateTime();
                    Clients[index].IsConnected= true;
                    break;
                }
                case ActionType::LogoutClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i++].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients[index].UpdateTime();
                    Clients[index].IsConnected= false;
                    break;
                }
                case ActionType::RenameClient:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i++].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    Clients[index].DisplayName=move(act.Util);
                }
                case ActionType::AddRoom:{
                    for(int i=0; i<Clients.size()&&!flag; flag=Clients[i++].ID==act.ActionRequester.ID);
                    if(flag)
                        return false;
                    //Search requested members
                    vector<RegisteredClient*> members;
                    for(int i=0; i<act.IDs.size();i++){
                        index=-1;
                        for(int j=0; i<Clients.size()&& !(index+1);index=(Clients[j++].ID==act.IDs[i])?j:index);
                        if(!(index+1))
                            return false;
                        members.push_back(&Clients[index]);
                    }

                    ChatRoomHost buildRoom=ChatRoomHost(act.ActionRequester.ID,act.Util);

                    for(auto & member : members)
                        buildRoom.PushMember(member);
                    index=-1;
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i++].ID==act.ActionRequester.ID)?i:index);
                    buildRoom.PromoteMember(&Clients[index]);
                    Rooms.push_back(buildRoom);
                    break;
                }
                case ActionType::RemoveRoom:{
                    for(int i=0; i<Rooms.size()&&!(index+1); index=(Rooms[i++].ID==act.IDs[0])?i:index);
                    if(!(index+1))
                        return false;
                    if(Rooms[index].CreatorID!=act.ActionRequester.ID){
                        std::cout<< "[SERVER]:[WARNING]: Unauthorized client attempted to delete a chatroom!\n\tAddress:"
                        << act.ActionRequester.Address.sin_addr.s_addr;
                        return false;
                    }
                    Rooms.erase(Rooms.begin()+index);
                    break;
                }
                case ActionType::RenameRoom:{
                    for(int i=0; i<Rooms.size()&&!(index+1); index=(Rooms[i++].ID==act.IDs[0])?i:index);
                    if(!(index+1))
                        return false;
                    for(int i=0; i<Rooms.size() && !flag; flag=Rooms[index].Managers[i++]->ID==act.ActionRequester.ID);
                    if(!flag)
                        return false;
                    Rooms[index].RoomName=move(act.Util);
                    break;
                }
                case ActionType::AddRoomMember:{
                    for(int i=0; i<Rooms.size()&&!(index+1); index=(Rooms[i++].ID==act.IDs[0])?i:index);
                    if(!(index+1))
                        return false;
                    for(int i=0; i<Rooms.size() && !flag; flag=Rooms[index].Managers[i++]->ID==act.ActionRequester.ID);
                    if(!flag)
                        return false;
                    vector<RegisteredClient*> toPush;
                    int rI=index;
                    for(unsigned long ID : act.IDs){
                        index=-1;
                        for(int j=0; j<Clients.size() && !(index+1); index=(Clients[j++].ID==ID)?j:index);
                        toPush.push_back(&Clients[index]);
                    }
                    index=rI;

                    for (auto cur: toPush)
                        Rooms[index].PushMember(cur);
                    break;
                }
                case ActionType::RemoveRoomMember:{
                    for(int i=0; i<Rooms.size()&&!(index+1); index=(Rooms[i++].ID==act.IDs[0])?i:index);
                    if(!(index+1))
                        return false;
                    for(int i=0; i<Rooms.size() && !flag; flag=Rooms[index].Managers[i++]->ID==act.ActionRequester.ID);
                    if(!flag)
                        return false;
                    vector<RegisteredClient*> toErase;
                    int rI=index;
                    for(unsigned long ID : act.IDs){
                        index=-1;
                        for(int j=0; j<Clients.size() && !(index+1); index=(Clients[j++].ID==ID)?j:index);
                        toErase.push_back(&Clients[index]);
                    }
                    index=rI;

                    for (auto cur: toErase)
                        Rooms[index].RemoveMember(cur);
                    break;
                }
                case ActionType::PromoteRoomMember:{
                    for(int i=0; i<Rooms.size()&&!(index+1); index=(Rooms[i++].ID==act.IDs[0])?i:index);
                    if(!(index+1))
                        return false;
                    if(Rooms[index].CreatorID!=act.ActionRequester.ID)
                        return false;

                    int rI=index;
                    RegisteredClient *toPromote;
                    index=-1;
                    for(int i=0; i<Clients.size() && !(index+1); index=(Clients[i++].ID==act.IDs[0])?i:index);
                    toPromote=&Clients[index];
                    index=rI;

                    Rooms[index].PromoteMember(toPromote);
                    break;
                }
                case ActionType::DemoteRoomMember:{
                    for(int i=0; i<Rooms.size()&&!(index+1); index=(Rooms[i++].ID==act.IDs[0])?i:index);
                    if(!(index+1))
                        return false;
                    if(Rooms[index].CreatorID!=act.ActionRequester.ID)
                        return false;

                    int rI=index;
                    RegisteredClient *toDemote;
                    index=-1;
                    for(int i=0; i<Clients.size() && !(index+1); index=(Clients[i++].ID==act.IDs[0])?i:index);
                    toDemote=&Clients[index];
                    index=rI;

                    Rooms[index].DemoteMember(toDemote);
                    break;
                }
                case ActionType::SendMessage:{
                    for(int i=0; i<Clients.size()&&!(index+1); index=(Clients[i++].ID==act.ActionRequester.ID)?i:index);
                    if(!(index+1))
                        return false;
                    int senderI=index;
                    index=-1;
                    for(int i=0; i<Rooms.size()&&!(index+1); index=(Rooms[i++].ID==act.IDs[0])?i:index);
                    if(!(index+1))
                        return false;
                    auto msg = Message(Clients[senderI].ID,act.IDs[0],act.Util);
                    Messages.push_back(msg);
                    Rooms[index].PushMessage(&Messages[Messages.size()-1]);
                    break;
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