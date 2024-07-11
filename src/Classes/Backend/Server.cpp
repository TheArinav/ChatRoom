#include <vector>
#include <iostream>
#include <queue>
#include <unistd.h>
#include <mutex>
#include <algorithm>
#include <sys/socket.h>
#include "../GeneralTypes/Message.h"
#include "RegisteredClient.h"
#include "ChatRoomHost.h"
#include "../GeneralTypes/ServerAction.h"
#include "Server.h"
#include "../GeneralTypes/ClientAction.h"

using std::vector;
using std::queue;
using std::mutex;
using std::lock_guard;
using GeneralTypes::Message;
using Backend::RegisteredClient;
using Backend::ChatRoomHost;
using GeneralTypes::ServerAction;
using GeneralTypes::ServerActionType;
using GeneralTypes::ClientAction;
using GeneralTypes::ClientActionType;

namespace Backend {
    /**
     * Builds a new server instance.
     */
    Server::Server(){
        Shutdown = false;
        ServerAction build = ServerAction(ServerActionType::ServerBuilt, RegisteredClient::Host);
        build.CompleteAction();
        Log.push_back(build);
    }

    //region Methods
    /**
     * Starts this server.
     */
    bool Server::Start(){
        ServerAction build = ServerAction(ServerActionType::ServerStarted, RegisteredClient::Host);
        build.CompleteAction();
        Log.push_back(build);
        while (!Shutdown) {
            if (ActionQueue.empty()) {
                continue;
            }

            ServerAction last;
            {
                lock_guard<mutex> guard(ActionQueueMutex);
                last = ActionQueue.front();
            }

            if (!EnactAction()) {
                std::cout << "[SERVER]:[ERROR]: Action failed:\n" << last.ToString() << "\n";
                GenerateResponse(&last, false);
            } else {
                std::cout << "[SERVER]:[INFO]: Action enacted! details:\n" << Log.back().ToString() << "\n";
                GenerateResponse(&last, true);
            }
            RollResponses();
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
        lock_guard<mutex> guard(ActionQueueMutex);
        if (!ActionQueue.empty() && ActionQueue.front().ID == act->ID) {
            return false;
        }
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
            lock_guard<mutex> guard(ActionQueueMutex);
            if (ActionQueue.empty()) {
                return false;
            }
            act = ActionQueue.front();
            ActionQueue.pop();
        }

        //region Verify Identity
        int reqInd = -1;
        for (int i = 0; i < Clients.size(); ++i) {
            if (Clients[i].ID == act.ActionRequester.ID) {
                reqInd = i;
                break;
            }
        }

        if (reqInd != -1 && Clients[reqInd].Address.sin_addr.s_addr != act.ActionRequester.Address.sin_addr.s_addr) {
            std::cout << "[SERVER]:[WARNING]: Attempted impersonation detected! By client with address:\n\t"
                      << act.ActionRequester.Address.sin_addr.s_addr << ":" << Clients[reqInd].Address.sin_addr.s_addr
                      << "\n";
            return false;
        }
        //endregion

        //region Temporary variables
        bool flag = false;
        int index = -1;
        //endregion

        switch (act.Type) {
            case ServerActionType::AddClient: {
                RegisteredClient newCl = RegisteredClient(act.ActionRequester.DisplayName, act.ActionRequester.Address);
                for (const auto &client : Clients) {
                    if (client.Address.sin_addr.s_addr == newCl.Address.sin_addr.s_addr) {
                        flag = true;
                        break;
                    }
                }
                if (flag) {
                    return false;
                }

                LastTouched = RegisteredClient(newCl);
                Clients.push_back(newCl);
                break;
            }
            case ServerActionType::RemoveClient: {
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.ActionRequester.ID) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }

                vector<vector<ClientAction>::iterator> toRemove;
                for (auto it = Responses.begin(); it != Responses.end(); ++it) {
                    if (it->RecipientAddress.sin_addr.s_addr == Clients[index].Address.sin_addr.s_addr) {
                        toRemove.push_back(it);
                    }
                }

                for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) {
                    Responses.erase(*it);
                }

                LastTouched = RegisteredClient(Clients[index]);
                Clients.erase(Clients.begin() + index);
                break;
            }
            case ServerActionType::LoginClient: {
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.ActionRequester.ID) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                Clients[index].UpdateTime();
                Clients[index].IsConnected = true;
                LastTouched = Clients[index];
                break;
            }
            case ServerActionType::LogoutClient: {
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.ActionRequester.ID) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                Clients[index].UpdateTime();
                Clients[index].IsConnected = false;
                LastTouched = Clients[index];
                break;
            }
            case ServerActionType::RenameClient: {
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.ActionRequester.ID) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                LastTouched = Clients[index];
                Clients[index].DisplayName = std::move(act.Util);
                break;
            }
            case ServerActionType::AddRoom: {
                for (const auto &client : Clients) {
                    if (client.ID == act.ActionRequester.ID) {
                        flag = true;
                        break;
                    }
                }
                if (flag) {
                    return false;
                }

                // Search requested members
                vector<RegisteredClient*> members;
                for (auto & id : act.IDs) {
                    index = -1;
                    for (int j = 0; j < Clients.size(); ++j) {
                        if (Clients[j].ID == id) {
                            index = j;
                            break;
                        }
                    }
                    if (index == -1) {
                        return false;
                    }
                    members.push_back(&Clients[index]);
                }

                ChatRoomHost buildRoom = ChatRoomHost(act.ActionRequester.ID, act.Util);
                for (auto & member : members) {
                    buildRoom.PushMember(member);
                }
                index = -1;
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.ActionRequester.ID) {
                        index = i;
                        break;
                    }
                }
                buildRoom.PromoteMember(&Clients[index]);
                LastTouched = buildRoom;
                Rooms.push_back(buildRoom);
                break;
            }
            case ServerActionType::RemoveRoom: {
                for (int i = 0; i < Rooms.size(); ++i) {
                    if (Rooms[i].ID == act.IDs[0]) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                if (Rooms[index].CreatorID != act.ActionRequester.ID) {
                    std::cout << "[SERVER]:[WARNING]: Unauthorized client attempted to delete a chatroom!\n\tAddress:"
                              << act.ActionRequester.Address.sin_addr.s_addr;
                    return false;
                }
                LastTouched = Rooms[index];
                Rooms.erase(Rooms.begin() + index);
                break;
            }
            case ServerActionType::RenameRoom: {
                for (int i = 0; i < Rooms.size(); ++i) {
                    if (Rooms[i].ID == act.IDs[0]) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                for (const auto & manager : Rooms[index].Managers) {
                    if (manager->ID == act.ActionRequester.ID) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    return false;
                }
                LastTouched = Rooms[index];
                Rooms[index].RoomName = std::move(act.Util);
                break;
            }
            case ServerActionType::AddRoomMember: {
                for (int i = 0; i < Rooms.size(); ++i) {
                    if (Rooms[i].ID == act.IDs[0]) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                for (const auto & manager : Rooms[index].Managers) {
                    if (manager->ID == act.ActionRequester.ID) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    return false;
                }
                vector<RegisteredClient*> toPush;
                int rI = index;
                for (size_t i = 1; i < act.IDs.size(); ++i) {
                    unsigned long long ID = act.IDs[i];
                    index = -1;
                    for (int j = 0; j < Clients.size(); ++j) {
                        if (Clients[j].ID == ID) {
                            index = j;
                            break;
                        }
                    }
                    toPush.push_back(&Clients[index]);
                }
                index = rI;

                LastTouched = Rooms[index];
                for (auto cur : toPush) {
                    Rooms[index].PushMember(cur);
                }
                break;
            }
            case ServerActionType::RemoveRoomMember: {
                for (int i = 0; i < Rooms.size(); ++i) {
                    if (Rooms[i].ID == act.IDs[0]) {
                        index = i;
                        break;
                    }
                }
                if (index == -1)
                    return false;

                //Check if requester is a manager.
                for (const auto & manager : Rooms[index].Managers) {
                    if (manager->ID == act.ActionRequester.ID) {
                        flag = true;
                        break;
                    }
                }
                //Check if manager is trying to kick another manager
                if(flag&&act.ActionRequester.ID!=Rooms[index].CreatorID)
                    for(unsigned long long ID : act.IDs)
                        for(auto & Manager : Rooms[index].Managers)
                            if(ID==Manager->ID)
                                return false;

                //Check if requester is trying to remove themselves
                flag=(flag)?flag:(act.IDs.size()==1 && act.IDs[0]==act.ActionRequester.ID);

                if (!flag)
                    return false;

                vector<RegisteredClient*> toErase;
                int rI = index;
                for (auto ID : act.IDs) {
                    index = -1;
                    for (int j = 0; j < Clients.size(); ++j) {
                        if (Clients[j].ID == ID) {
                            index = j;
                            break;
                        }
                    }
                    toErase.push_back(&Clients[index]);
                }
                index = rI;

                LastTouched = Rooms[index];
                for (auto cur : toErase) {
                    Rooms[index].RemoveMember(cur);
                }
                break;
            }
            case ServerActionType::PromoteRoomMember: {
                for (int i = 0; i < Rooms.size(); ++i) {
                    if (Rooms[i].ID == act.IDs[0]) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                if (Rooms[index].CreatorID != act.ActionRequester.ID) {
                    return false;
                }

                int rI = index;
                RegisteredClient *toPromote;
                index = -1;
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.IDs[1]) {
                        index = i;
                        break;
                    }
                }
                toPromote = &Clients[index];
                index = rI;

                LastTouched = toPromote;
                Rooms[index].PromoteMember(toPromote);
                break;
            }
            case ServerActionType::DemoteRoomMember: {
                for (int i = 0; i < Rooms.size(); ++i) {
                    if (Rooms[i].ID == act.IDs[0]) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                if (Rooms[index].CreatorID != act.ActionRequester.ID) {
                    return false;
                }

                int rI = index;
                RegisteredClient *toDemote;
                index = -1;
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.IDs[1]) {
                        index = i;
                        break;
                    }
                }
                toDemote = &Clients[index];
                index = rI;

                LastTouched = toDemote;
                Rooms[index].DemoteMember(toDemote);
                break;
            }
            case ServerActionType::SendMessage: {
                for (int i = 0; i < Clients.size(); ++i) {
                    if (Clients[i].ID == act.ActionRequester.ID) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                int senderI = index;
                index = -1;
                for (int i = 0; i < Rooms.size(); ++i) {
                    if (Rooms[i].ID == act.IDs[0]) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    return false;
                }
                auto msg = Message(Clients[senderI].ID, act.IDs[0], act.Util);
                LastTouched = msg;
                Messages.push_back(msg);
                Rooms[index].PushMessage(&Messages.back());
                break;
            }
            default: {
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

    void Server::GenerateResponse(ServerAction *act, bool success) {
        ClientAction clientAction = {};
        clientAction.RecipientAddress = act->ActionRequester.Address;
        clientAction.Type = (success) ? ClientActionType::InformSuccess : ClientActionType::InformFailure;
        clientAction.Data << std::to_string(static_cast<int>(act->Type));
        if (success) {
            try {
                switch (act->Type) {
                    case ServerActionType::AddClient: {
                        auto cl = std::any_cast<RegisteredClient>(LastTouched);
                        clientAction.Data << std::to_string(cl.ID)
                                          << cl.DisplayName
                                          << std::to_string(cl.Address.sin_addr.s_addr);
                        break;
                    }
                    case ServerActionType::RemoveClient: {
                        auto cl = std::any_cast<RegisteredClient>(LastTouched);
                        clientAction.Data << std::to_string(cl.ID)
                                          << cl.DisplayName
                                          << std::to_string(cl.Address.sin_addr.s_addr);
                        break;
                    }
                    case ServerActionType::LoginClient: {
                        auto cl = std::any_cast<RegisteredClient>(LastTouched);
                        clientAction.Data << std::to_string(cl.ID);
                        break;
                    }
                    case ServerActionType::LogoutClient: {
                        auto cl = std::any_cast<RegisteredClient>(LastTouched);
                        clientAction.Data << std::to_string(cl.ID);
                        break;
                    }
                    case ServerActionType::RenameClient: {
                        auto cl = std::any_cast<RegisteredClient>(LastTouched);
                        clientAction.Data << std::to_string(cl.ID)
                                          << cl.DisplayName << act->Util;
                        break;
                    }
                    case ServerActionType::AddRoom: {
                        auto createdRoom = std::any_cast<ChatRoomHost>(LastTouched);
                        vector<ClientAction> InformMembers;
                        for (auto curClient: createdRoom.Members) {
                            ClientAction informCurrent = {};
                            informCurrent.Type = ClientActionType::JoinedRoom;
                            informCurrent.RecipientAddress = curClient->Address;
                            informCurrent.Data << std::to_string(createdRoom.ID) << createdRoom.RoomName;
                            Responses.push_back(informCurrent);
                        }
                        break;
                    }
                    case ServerActionType::RemoveRoom: {
                        auto createdRoom = std::any_cast<ChatRoomHost>(LastTouched);
                        vector<ClientAction> InformMembers;
                        for (auto curClient: createdRoom.Members) {
                            ClientAction informCurrent = {};
                            informCurrent.Type = ClientActionType::LeftRoom;
                            informCurrent.RecipientAddress = curClient->Address;
                            informCurrent.Data << std::to_string(createdRoom.ID) << createdRoom.RoomName;
                            Responses.push_back(informCurrent);
                        }
                        break;
                    }
                    case ServerActionType::RenameRoom: {
                        auto roomHost = std::any_cast<ChatRoomHost>(LastTouched);
                        clientAction.Data << std::to_string(roomHost.ID)
                                          << roomHost.RoomName << act->Util;
                        break;
                    }
                    case ServerActionType::AddRoomMember: {
                        vector<RegisteredClient *> Difference =
                                SetSubtractionMembers(Rooms[act->IDs[0]].Members,
                                                      (std::any_cast<ChatRoomHost>(LastTouched)).Members);

                        for (auto curClient : Difference) {
                            ClientAction informCurrent = {};
                            informCurrent.Type = ClientActionType::JoinedRoom;
                            clientAction.RecipientAddress = curClient->Address;
                            clientAction.Data << std::to_string(Rooms[act->IDs[0]].ID) << Rooms[act->IDs[0]].RoomName;
                            Responses.push_back(informCurrent);
                        }
                        break;
                    }
                    case ServerActionType::RemoveRoomMember: {
                        vector<RegisteredClient *> Difference =
                                SetSubtractionMembers((std::any_cast<ChatRoomHost>(LastTouched)).Members,
                                                      Rooms[act->IDs[0]].Members);

                        for (auto curClient: Difference) {
                            ClientAction informCurrent = {};
                            informCurrent.Type = ClientActionType::LeftRoom;
                            clientAction.RecipientAddress = curClient->Address;
                            clientAction.Data << std::to_string(Rooms[act->IDs[0]].ID) << Rooms[act->IDs[0]].RoomName;
                            Responses.push_back(informCurrent);
                        }
                        break;
                    }
                    case ServerActionType::PromoteRoomMember: {
                        clientAction.Data << std::any_cast<RegisteredClient>(LastTouched).ID;
                        ClientAction informPromoted = {};
                        informPromoted.Type = GeneralTypes::ClientActionType::Promoted;
                        informPromoted.Data << act->IDs[0];
                        informPromoted.RecipientAddress = std::any_cast<RegisteredClient>(LastTouched).Address;
                        Responses.push_back(informPromoted);
                        break;
                    }
                    case ServerActionType::DemoteRoomMember: {
                        clientAction.Data << std::any_cast<RegisteredClient>(LastTouched).ID;
                        ClientAction informDemoted = {};
                        informDemoted.Type = GeneralTypes::ClientActionType::Demoted;
                        informDemoted.Data << act->IDs[0];
                        informDemoted.RecipientAddress = std::any_cast<RegisteredClient>(LastTouched).Address;
                        Responses.push_back(informDemoted);
                        break;
                    }
                    case ServerActionType::SendMessage: {
                        auto msg = std::any_cast<Message>(LastTouched);
                        clientAction.Data << msg.ID;
                        int roomI = -1;
                        for (int i = 0; i < Rooms.size(); ++i) {
                            if (Rooms[i].ID == msg.TargetChatRoomID) {
                                roomI = i;
                                break;
                            }
                        }
                        if (roomI == -1) {
                            return;
                        }
                        for (auto member : Rooms[roomI].Members) {
                            if (member->ID != msg.ClientID) {
                                ClientAction informCurrent = {};
                                informCurrent.Type = GeneralTypes::ClientActionType::ReceivedMessage;
                                informCurrent.RecipientAddress = member->Address;
                                informCurrent.Data << msg.ID << msg.Contents;
                                Responses.push_back(informCurrent);
                            }
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Bad any_cast in GenerateResponse: " << e.what() << std::endl;
                clientAction.Type = ClientActionType::InformFailure;
            }
        }
        Responses.push_back(clientAction);
    }

    void Server::RollResponses() {
        std::vector<std::vector<ClientAction>::iterator> toRemove;

        for (auto it = Responses.begin(); it != Responses.end(); ++it) {
            bool found = false;

            for (auto& client : Clients) {
                if (client.Address.sin_addr.s_addr == it->RecipientAddress.sin_addr.s_addr) {
                    found = true;
                    if (client.IsConnected) {
                        std::string serializedData = it->Serialize();

                        int sock = socket(AF_INET, SOCK_STREAM, 0);
                        if (sock < 0) {
                            std::cerr << "[SERVER]:[ERROR]: Unable to create socket for response." << std::endl;
                            toRemove.push_back(it);
                            break;
                        }

                        if (connect(sock, (struct sockaddr*)&client.Address, sizeof(client.Address)) < 0) {
                            std::cerr << "[SERVER]:[ERROR]: Unable to connect to client for response." << std::endl;
                            close(sock);
                            toRemove.push_back(it);
                            break;
                        }

                        if (send(sock, serializedData.c_str(), serializedData.size(), 0) < 0) {
                            std::cerr << "[SERVER]:[ERROR]: Unable to send response to client." << std::endl;
                        } else {
                            std::cout << "[SERVER]:[INFO]: Response sent to client: " << client.DisplayName << std::endl;
                        }

                        close(sock);
                        toRemove.push_back(it);
                    }
                    break;
                }
            }

            if (!found) {
                toRemove.push_back(it);
            }
        }

        // Erase the responses that were either sent or where the client was not found
        for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) {
            Responses.erase(*it);
        }
    }

    std::vector<RegisteredClient *> Server::SetSubtractionMembers(const vector<RegisteredClient *> &vec1, const vector<RegisteredClient *> &vec2) {
        std::vector<RegisteredClient*> result;

        // Create sorted copies of the input vectors
        std::vector<RegisteredClient*> sorted_vec1 = vec1;
        std::vector<RegisteredClient*> sorted_vec2 = vec2;

        // Sort the vectors using custom comparator for pointers
        auto cmp = [](const RegisteredClient* lhs, const RegisteredClient* rhs) {
            return lhs->ID < rhs->ID;
        };

        std::sort(sorted_vec1.begin(), sorted_vec1.end(), cmp);
        std::sort(sorted_vec2.begin(), sorted_vec2.end(), cmp);

        // Perform set difference
        std::set_difference(sorted_vec1.begin(), sorted_vec1.end(),
                            sorted_vec2.begin(), sorted_vec2.end(),
                            std::back_inserter(result), cmp);

        return result;
    }
    //endregion
} // Backend
