//
// Created by ariel on 7/5/2024.
//

#ifndef CHATROOMSERVER_MESSEGE_H
#define CHATROOMSERVER_MESSEGE_H


#include <string>

typedef std::string string;
namespace GeneralTypes {
    class Messege {
    public:
        long ClientID;
        long TargetChatRoomID;
        string Contents;
    };
}


#endif //CHATROOMSERVER_MESSEGE_H
