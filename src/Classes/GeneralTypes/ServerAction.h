#ifndef SERVER_ACTION_H
#define SERVER_ACTION_H

#include <ctime>
#include <chrono>
#include "../Backend/RegisteredClient.h"

using Backend::RegisteredClient;

namespace GeneralTypes {

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
        RegisteredClient ActionRequester;

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
        /**
         * Used to store logical identifiers of Messages/Clients/Rooms.
         */
        vector<unsigned long> IDs;
        /**
         * Used to store ChatRoom/Client names or Message contents
         */
        string Util;
        //endregion
        /**
         * Create a new server action instance.
         */
        ServerAction(ActionType type, RegisteredClient requester);
        /**
         * Used to note that the action was enacted by the server.
         * @return
         */
        void CompleteAction();
        /**
         * Serializes this object to a human-readable format
         * @return
         */
        string ToString() const;
        /**
         * Serializes this object for transfer through a socket.
         * @return
         */
        string Serialize() const;
        /**
         * Deserializes a packet back into the object
         * @param data
         * @return
         */
        static ServerAction Deserialize(const string& data);
    private:
        /**
         * The amount of server actions created. Used for assigning addresses.
         */
        static int count;
    };

} // namespace Backend

#endif // SERVER_ACTION_H
