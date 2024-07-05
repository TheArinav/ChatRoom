#include <string>

using std::string;
using std::move;

namespace GeneralTypes{
    class Message {
    public:
        //region Properties
        /**
         * Logical identifier of message sender.
         */
        long ClientID;
        /**
         * Logical identifier of recipient chat room.
         */
        long TargetChatRoomID;
        /**
         * Message contents.
         */
        string Contents;
        //endregion

        //region Constructors/Destructors
        /**
         * Create an empty Message object.
         */
        Message() : ClientID(0), TargetChatRoomID(0), Contents("") {}
        /**
         * Create a Message object.
         * @param ClientID Logical identifier of message sender.
         * @param TargetChatRoomID Logical identifier of recipient chat room.
         * @param Contents Message contents.
         */
        Message(long ClientID,long TargetChatRoomID,string Contents) :  ClientID(ClientID), TargetChatRoomID(TargetChatRoomID), Contents(move(Contents)) {}
        //endregion
    };
}