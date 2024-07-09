#include <ctime>
#include <chrono>
#include <sstream>
#include "../Backend/RegisteredClient.h"
#include "ServerAction.h"

using Backend::RegisteredClient;
using std::chrono::system_clock;
using std::to_string;
using GeneralTypes::ActionType;
using GeneralTypes::ServerAction;

namespace GeneralTypes {
    int ServerAction::count=0;
    /**
    * Create a new server action instance.
    */
    ServerAction::ServerAction(ActionType type, RegisteredClient requester):
    Type(type), ID(count++), ActionRequester(requester),
    TimeRegistered(system_clock::to_time_t(system_clock::now())), TimeComplete((time_t)(-1))
    {}
    /**
    * Used to noted that the action was enacted by the server.
    * @return
    */
    void ServerAction::CompleteAction(){
            TimeComplete=system_clock::to_time_t(system_clock::now());
    }
    string ServerAction::ToString() const {
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
    string ServerAction::Serialize() const{
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
    ServerAction ServerAction::Deserialize(const string& data) {
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
} // Backend