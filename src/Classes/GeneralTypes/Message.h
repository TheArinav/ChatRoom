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
        //region Properties
        /**
        * Logical identifier of a Message object.
        */
        unsigned long ID;
        /**
         * Logical identifier of message sender.
         */
        unsigned long ClientID;
        /**
         * Logical identifier of recipient chat room.
         */
        unsigned long TargetChatRoomID;
        //endregion

        //region Constructors/Destructors
        /**
         * Create an empty Message object.
         */
        Message();
        /**
         * Create a Message object.
         * @param ClientID Logical identifier of message sender.
         * @param TargetChatRoomID Logical identifier of recipient chat room.
         * @param Contents Message contents.
         */
        Message(long ClientID,long TargetChatRoomID,string Contents);
        //endregion
    private:
        /**
         * Stores number of created messages. Used to assign IDs.
         */
        static int count;
    };
}


#endif //CHATROOMSERVER_MESSEGE_H
