#include <vector>
#include <string>
#include "../GeneralTypes/Message.h"
#include "RegisteredClient.h"

using std::vector;
using std::string;
using GeneralTypes::Message;
using std::next;

namespace Backend {
    class ChatRoomHost {
    public:
        //region Properties
        /**
         * @brief The logical ID of the ChatRoomHost instance.
         */
        unsigned long ID;
        /**
         * @breif Display name for the ChatRoomHost instance.
         */
        string RoomName;
        /**
         * @brief The logical ID of the primary owner of the ChatRoomHost instance.
         */
        unsigned long CreatorID;
        /**
         * @brief The secondary owners of the ChatRoomHost instance.
         */
        vector<RegisteredClient*> Managers;
        /**
         * @brief The client members of the ChatRoomHost instance. (Includes all ranks)
         */
        vector<RegisteredClient*> Members;
        /**
         * All messages visible in the ChatRoomHost instance.
         */
        vector<Message*> MessageList;
        //endregion

        //region Constructors
        /**
         * Create a new ChatRoomHost instance.
         * @param creatorID Logical id of the creator client.
         * @param roomName Display name for the room.
         */
        ChatRoomHost(unsigned long creatorID, string roomName)
        : ID(count++),CreatorID(creatorID), RoomName(roomName){}
        //endregion

        //region 'Add' Methods
        /**
        * Add a new latest message to the chatroom.
        * @param msg Latest message to add.
        * @return Whether the message was successfully added.
        */
        bool PushMessage(Message* msg){
            if (SearchMessage(msg))
                return false;
            if (!SearchMember(msg->ClientID))
                return false;
            if (msg->TargetChatRoomID==this->ID)
                return false;
            MessageList.push_back(msg);
            return true;
        }
        /**
         * Add a new member to the chatroom.
         * @param client Client to add.
         * @return Whether the client was successfully added.
         */
        bool PushMember(RegisteredClient *client){
            if(SearchMember(client->ID))
                return false;
            Members.push_back(client);
            return true;
        }
        /**
         * Add an EXISTING member to the manager list
         * @param client Client member to promote to manager.
         * @return Whether the client was successfully promoted.
         */
        bool PromoteMember(RegisteredClient *client){
            if (!SearchMember(client->ID))
                return false;
            if (SearchManager(client->ID))
                return false;
            Managers.push_back(client);
            return true;
        }
        //endregion

        //region 'Remove' Methods
        /**
         * Delete a message from the chatroom.
         * @param msg Message to delete.
         * @return Whether the message was successfully deleted.
         */
        bool RemoveMessage(Message *msg){
            if(!SearchMessage(msg))
                return false;
            MessageList.erase(next(MessageList.begin(), FindMessage(msg->ID)));
            return true;
        }
        /**
         * Remove a member from the chatroom.
         * @param client Client member to remove.
         * @return Whether the member was successfully removed or not.
         */
        bool RemoveMember(RegisteredClient *client){
            if(!SearchMember(client->ID))
                return false;
            Members.erase(next(Members.begin(), FindMember(client->ID)));
            return true;
        }
        /**
         * Remove manager permissions from a member
         * @param client Client member to demote.
         * @return Whether the member was successfully demoted.
         */
        bool DemoteMember(RegisteredClient *client){
            if(!SearchManager(client->ID))
                return false;
            Managers.erase(next(Managers.begin(), FindManager(client->ID)));
            return true;
        }
        //endregion

    private:
        /**
         * Number of ChatRoomHost instances created. Used for assigning logical IDs.
         */
        static int count;

        //region 'Search' methods
        /**
         * Check if a message is registered in the chatroom.
         * @param msg Message to search.
         * @return Whether the message was found.
         */
        bool SearchMessage(Message *msg){
            unsigned long id = msg->ID;
            bool isFound = false;
            for(int i=0; i<MessageList.size(); isFound=(MessageList[i++]->ID==id));
            return isFound;
        }
        /**
         * Check id a client is registered as a member of this chatroom.
         * @param id Client member ID to search.
         * @return Whether the client was found.
         */
        bool SearchMember(unsigned long id){
            bool isFound = false;
            for(int i=0; i<Members.size(); isFound=(Members[i++]->ID==id));
            return isFound;
        }
        /**
         * Check if a client is registered as a manager member of this chatroom.
         * @param id Client id to search.
         * @return Whether the client was found in the managers list.
         */
        bool SearchManager(unsigned long id){
            bool isFound = false;
            for(int i=0; i<Managers.size(); isFound=(Managers[i++]->ID==id));
            return isFound;
        }
        //endregion

        //region 'Find' methods
        /**
         * Given that a message exists, find the index where it's pointer is stored in the vector.
         * @param id Message ID to find.
         * @return The message index.
         * @warning Returns -1 if the message was not found.
         */
        int FindMessage(unsigned long id){
            int index = -1;
            for(int i=0; i<Managers.size(); index=(MessageList[i++]->ID==id)?i:index);
            return index;
        }
        /**
         * Given that a member exists, find the index where it's pointer is stored in the vector.
         * @param id Member client ID to find.
         * @return The member index.
         * @warning Returns -1 if the member was not found.
         */
        int FindMember(unsigned long id){
            int index = -1;
            for(int i=0; i<Members.size(); index=(Members[i++]->ID==id)?i:index);
            return index;
        }
        /**
         * Given that a manager member exists, find the index where it's pointer is stored in the vector.
         * @param id Manager member client ID to find.
         * @return The manager member index.
         * @warning Returns -1 if the manager member was not found.
         */
        int FindManager(unsigned long id){
            int index = -1;
            for(int i=0; i<Managers.size(); index=(Managers[i++]->ID==id)?i:index);
            return index;
        }
        //endregion
    };
} // Backend