//
// Created by ariel on 7/5/2024.
//

#ifndef CHATROOMSERVER_MESSEGE_H
#define CHATROOMSERVER_MESSEGE_H


#include <string>

using std::string;

namespace GeneralTypes {
    class Message {
    public:
        long ClientID;
        long TargetChatRoomID;
        string Contents;
        Message();
        Message(long,long,string);
    };
}


#endif //CHATROOMSERVER_MESSEGE_H
