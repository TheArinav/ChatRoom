//
// Created by ariel on 7/5/2024.
//

#include "RegisteredClient.h"
#include <string>
#include <stack>



typedef std::string string;
typedef std::stack<string> StringStack;

namespace Backend {
    class RegisteredClient {
    public:
        long ID;
        string DisplayName;
    };
} // Backend