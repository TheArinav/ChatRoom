//
// Created by ariel on 7/5/2024.
//

#include <queue>
#include "Message.h"
#include "MessageQueue.h"

using std::queue;
using std::deque;
using GeneralTypes::MessageQueue;
using GeneralTypes::Message;

namespace GeneralTypes {
    /**
    * Allows to view the contents of the stack.
    * @return
    */
    const deque<Message> &MessageQueue::ViewContainer() {
        return this->c;
    }
}