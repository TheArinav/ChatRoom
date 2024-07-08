#ifndef SERVER_ACTION_H
#define SERVER_ACTION_H

#include <ctime>
#include <chrono>
#include "../Backend/RegisteredClient.h"
#include "ActionMetaData.h"

namespace Backend {

    enum class ActionType {
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

    class ServerAction {
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
        std::time_t TimeRegistered;

        /**
         * System time when the server has completed enacting the action.
         */
        std::time_t TimeComplete;

        /**
         * Used to check if the server had already enacted this action.
         */
        bool IsComplete;
        //endregion

        /**
         * Create a new server action instance.
         */
        ServerAction(ActionType type, RegisteredClient requester);

        /**
         * Used to note that the action was enacted by the server.
         * @return
         */
        bool CompleteAction();

        string ToString() const;
        string Serialize() const;
        static ServerAction Deserialize(const string& data);
    private:
        /**
         * The amount of server actions created. Used for assigning addresses.
         */
        static int count;
    };

} // namespace Backend

#endif // SERVER_ACTION_H
