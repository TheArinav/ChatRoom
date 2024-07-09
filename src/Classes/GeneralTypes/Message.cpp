#include <string>
#include "Message.h"

using std::string;
using std::move;
using GeneralTypes::Message;

namespace GeneralTypes{
    int Message::count=0;
    Message::Message() : ClientID(-1), TargetChatRoomID(-1), Contents("Null Message") {}
    /**
    * Create a Message object.
    * @param ClientID Logical identifier of message sender.
    * @param TargetChatRoomID Logical identifier of recipient chat room.
    * @param Contents Message contents.
     */
     Message::Message(unsigned long ClientID,unsigned long TargetChatRoomID,string Contents) : ID(count++), ClientID(ClientID), TargetChatRoomID(TargetChatRoomID), Contents(move(Contents)) {}
     //endregion
}