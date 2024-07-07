#include <vector>
#include <string>
#include "../GeneralTypes/Message.h"
#include "ChatRoomHost.h"
#include "RegisteredClient.h"

using std::vector;

#ifndef CHATROOMSERVER_ACTIONMETADATA_H
#define CHATROOMSERVER_ACTIONMETADATA_H

namespace Backend {
    /**
     * Used to store action data.
     */
    class ActionMetaData {
        vector<Message*> Messages;
        vector<RegisteredClient*> Clients;
        vector<ChatRoomHost*> Rooms;
        vector<string> Desc;
        vector<void*> Util;
    };

} // Backend

#endif //CHATROOMSERVER_ACTIONMETADATA_H
