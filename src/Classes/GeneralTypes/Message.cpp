#include <string>

using std::string;
using std::move;

namespace GeneralTypes{
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
        /**
         * Message contents.
         */
        string Contents;
        //endregion

        //region Constructors/Destructors
        /**
         * Create an empty Message object.
         */
        Message() : ClientID(-1), TargetChatRoomID(-1), Contents("Null Message") {}
        /**
         * Create a Message object.
         * @param ClientID Logical identifier of message sender.
         * @param TargetChatRoomID Logical identifier of recipient chat room.
         * @param Contents Message contents.
         */
        Message(long ClientID,long TargetChatRoomID,string Contents) : ID(count++), ClientID(ClientID), TargetChatRoomID(TargetChatRoomID), Contents(move(Contents)) {}
        //endregion
    private:
        /**
         * Stores number of created messages. Used to assign IDs.
         */
        static int count;
    };
}