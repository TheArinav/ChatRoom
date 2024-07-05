//
// Created by ariel on 7/5/2024.
//

#ifndef CHATROOMSERVER_EXPOSEDSTACK_H
#define CHATROOMSERVER_EXPOSEDSTACK_H

#include <queue>
#include "Message.h"

using std::queue;
using std::deque;

namespace GeneralTypes {

    class MessageQueue : public queue<Message>{
    public:
        const deque<Message>& ViewContainer();
    private:
        using std::queue<Message>::c;
};


} // GeneralTypes

#endif //CHATROOMSERVER_EXPOSEDSTACK_H
