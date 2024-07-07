#include <time.h>
#include <chrono>
#include "RegisteredClient.h"
#include "ActionMetaData.h"

using Backend::ActionMetaData;
using Backend::RegisteredClient;
using std::chrono::system_clock;

namespace Backend {
    enum class ActionType{
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
        ForwardMessage
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
        RegisteredClient *ActionRequester;
        /**
         * System time when the action object was built on the backend.
         */
        time_t TimeRegistered;
        /**
         * System time when the server has completed enacting the action.
         */
        time_t TimeComplete;
        /**
         * Additional data about the action.
         */
        ActionMetaData MetaData;
        /**
         * Used to check if the server had already enacted this action.
         */
        bool IsComplete;
        //endregion

        /**
         * Create a new server action instance.
         */
        ServerAction(ActionType type, RegisteredClient *requester, ActionMetaData meta):
        Type(type), ID(count++), ActionRequester(requester),TimeRegistered(system_clock::to_time_t(system_clock::now())),
        MetaData(meta){}

        /**
         * Used to noted that the action was enacted by the server.
         * @return
         */
        bool CompleteAction(){
            if(IsComplete)
                return false;
            IsComplete= true;
            TimeComplete=system_clock::to_time_t(system_clock::now());
            return true;
        }

    private:
        /**
         * The amount of server actions created. Used for assigning addresses.
         */
        static int count;
    };
} // Backend