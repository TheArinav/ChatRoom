#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <queue>
#include "../GeneralTypes/Message.h"
#include "RegisteredClient.h"
#include "ChatRoomHost.h"
#include "ServerAction.h"

using std::vector;
using std::queue;
using GeneralTypes::Message;
using Backend::RegisteredClient;
using Backend::ChatRoomHost;
using Backend::ServerAction;

namespace Backend {
    class Server{
    public:
        vector<Message> Messages;
        vector<RegisteredClient> Clients;
        vector<ChatRoomHost> Rooms;
        queue<ServerAction> ActionQueue;

        bool RegisterClient(sockaddr_in address, string uName);
    };
} // Backend