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
    };

} // GeneralTypes

#endif //CHATROOMSERVER_CLIENTACTION_H
