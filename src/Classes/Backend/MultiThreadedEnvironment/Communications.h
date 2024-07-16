#ifndef CHATROOMSERVER_COMMUNICATIONS_H
#define CHATROOMSERVER_COMMUNICATIONS_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include <vector>
#include <memory>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <atomic>

using namespace std;

namespace backend::multi_thread_serv {
    typedef addrinfo AddressInfo;
    struct ClientConnection {
        unsigned long long ClientID;
        thread ManagerThread;
        int SocketFD;
        sockaddr_storage Address;
    };

    class Communications {
    public:
        Communications();

        ~Communications();

        void Start(void (*clientListenFunc)(int));

        void Stop();

        int ServerFD;
        AddressInfo *ServerSocket;
        vector<ClientConnection> ClientConnections;

        void (*ClientListen)(int);

    private:
        void Setup();

        AddressInfo *SetAddr();

        void CreateSock();

        void Bind();

        void Listen();

        thread ListenThread;
        atomic<bool> Running{};
    };
}

#endif //CHATROOMSERVER_COMMUNICATIONS_H
