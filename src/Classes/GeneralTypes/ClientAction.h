//
// Created by IMOE001 on 7/9/2024.
//

#ifndef CHATROOMSERVER_CLIENTACTION_H
#define CHATROOMSERVER_CLIENTACTION_H
#include <string>
#include <netinet/in.h>

using std::string;

namespace GeneralTypes {
    enum class ClientActionType{
        InformFailure,
        InformSuccess,
        ReceiveMessage,
        JoinRoom,
        Promoted,
        Demoted,
        LeaveRoom
    };
    class ClientAction {
    public:
        //region Properties
        /**
         * Type of the action.
         */
        ClientActionType Type;
        /**
         * Data to transfer.
         */
        string Data;
        /**
         * Notes the target address.
         * @note This parameter will not be included when serializing.
         */
        sockaddr_in RecipientAddress;
        //endregion
        //region Constructors
        /**
         * Create an empty ClientAction
         */
        ClientAction();
        /**
         * Create a new instance of a ClientAction
         */
        ClientAction(ClientActionType,string ,sockaddr_in={});
        //endregion
        //region Methods
        /**
         * Serialize this ClientAction into a human-readable format.
         */
        string ToString();
        /**
         * Serialize this ClientAction to be transferred through a socket.
         */
        string Serialize();
        /**
         * Transform a string back into a ClientAction object.
         */
        static ClientAction Deserialize(string);
        //endregion
    };

} // GeneralTypes

#endif //CHATROOMSERVER_CLIENTACTION_H
