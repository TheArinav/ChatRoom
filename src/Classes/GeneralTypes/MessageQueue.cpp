//
// Created by ariel on 7/5/2024.
//

#include <queue>
#include "Message.h"

using std::queue;
using std::deque;

namespace GeneralTypes {
    class MessageQueue : public queue<Message> {
    public:
        /**
         * Allows to view the contents of the stack.
         * @return
         */
        const deque<Message>& ViewContainer() const {
            return this->c;
        }

    private:
        using queue<Message>::c;
    };
} // GeneralTypes