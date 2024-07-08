#include <time.h>
#include <chrono>
#include <sstream>
#include "../Backend/RegisteredClient.h"
#include "ActionMetaData.h"

using Backend::ActionMetaData;
using Backend::RegisteredClient;
using std::chrono::system_clock;
using std::to_string;

namespace Backend {
    enum class ActionType{
        ServerBuilt,
        ServerStarted,
        AddClient,
        RemoveClient,
        LoginClient,
        LogoutClient,
        RenameClient,
        AddRoom,
        RemoveRoom,
        RenameRoom,
        AddRoomMember,
        RemoveRoomMember,
        PromoteRoomMember,
        DemoteRoomMember,
        SendMessage,
        EditMessage,
        DeleteMessage,
        ForwardMessage,
        SendFriendRequest,
        AnswerFriendRequest
    };
    class ServerAction{
    public:
        //region Properties
        /**
         * Type of the action.
         */
        ActionType Type;
        /**
         * Logical ID of the action.
         */
        unsigned long ID;
        /**
         * Client who requested the action.
         */
        RegisteredClient ActionRequester;
        /**
         * System time when the action object was built on the backend.
         */
        time_t TimeRegistered;
        /**
         * System time when the server has completed enacting the action.
         */
        time_t TimeComplete;
        /**
         * Client/ChatRoom/Message IDs that are involved.
         */
        vector<long> IDs;
        /**
         * Used to store ChatRoom/Client names or Message contents
         */
        string Util;
        //endregion

        /**
         * Create a new server action instance.
         */
        ServerAction(ActionType type, RegisteredClient requester):
        Type(type), ID(count++), ActionRequester(move(requester)),
        TimeRegistered(system_clock::to_time_t(system_clock::now())), TimeComplete((time_t)(-1))
        {}

        /**
         * Used to noted that the action was enacted by the server.
         * @return
         */
        void CompleteAction(){
            TimeComplete=system_clock::to_time_t(system_clock::now());
        }
        string ToString() const {
            std::stringstream ss;
            ss << "ServerAction { "
               << "Type: " << static_cast<int>(Type) << ", "
               << "ID: " << ID << ", "
               << "ActionRequester: " <<  to_string(ActionRequester.ID) + " " + ActionRequester.DisplayName << ", "
               << "TimeRegistered: " << std::ctime(&TimeRegistered) << ","
               << "TimeComplete: " << (std::ctime(&TimeComplete))
               << " }";
            return ss.str();
        }
        string Serialize() const{
            string IDs_String;
            for(int i=0;i<IDs.size();IDs_String+= to_string(IDs[i++]));
            IDs_String = "[" + IDs_String + "]";
            std::stringstream ss;
            ss << static_cast<int>(Type) << " "
            << ID << " "
            << ActionRequester.ID << " "
            << ActionRequester.DisplayName << " "
            << ActionRequester.Address.sin_addr.s_addr << " "
            << ActionRequester.Address.sin_port << " "
            << ActionRequester.Address.sin_zero << " "
            << ActionRequester.Address.sin_family << " "
            << IDs_String << " "
            << Util;
            return ss.str();
        }
        static ServerAction Deserialize(const string& data) {
            std::istringstream iss(data);
            int type;
            unsigned long id;
            RegisteredClient requester;
            string ids_string, util;

            iss >> type >> id
                >> requester.ID >> requester.DisplayName
                >> requester.Address.sin_addr.s_addr
                >> requester.Address.sin_port
                >> requester.Address.sin_zero
                >> requester.Address.sin_family
                >> ids_string >> util;

            // Parse IDs from the string
            vector<int> ids;
            ids_string = ids_string.substr(1, ids_string.size() - 2); // Remove the surrounding brackets
            std::istringstream ids_stream(ids_string);
            string id_str;
            while (std::getline(ids_stream, id_str, ',')) {
                ids.push_back(std::stoi(id_str));
            }

            auto action_type = static_cast<ActionType>(type);
            ServerAction action(action_type, requester);
            action.IDs = move(action.IDs);
            action.Util = move(util);

            return action;
        }
    private:
        /**
         * The amount of server actions created. Used for assigning addresses.
         */
        static int count;
    };

} // Backend