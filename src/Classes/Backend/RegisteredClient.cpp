//
// Created by ariel on 7/5/2024.
//
#include <iostream>
#include <string>
#include <stack>
#include <netinet/in.h>
#include <vector>
#include <chrono>

#include "RegisteredClient.h"
#include "../GeneralTypes/Message.h"
#include "../GeneralTypes/MessageQueue.h"

using std::string;
using std::vector;
using std::move;
using GeneralTypes::Message;
using GeneralTypes::MessageQueue;
using Backend::RegisteredClient;

namespace Backend {
    int RegisteredClient::count = 0;

    //region Constructors/Destructors
    RegisteredClient::~RegisteredClient() = default;

    RegisteredClient::RegisteredClient() = default;

    /*!
    * Create new RegisteredClient instance
        * @param DisplayName The display name of the client.
         * @param Address     Address of the client.
         */
    RegisteredClient::RegisteredClient(string DisplayName, sockaddr_in Address)
            : ID(count++), DisplayName(move(DisplayName)), Address(Address),
              IsConnected(false), LastActivity(){}
    //endregion

    //region Methods
    /**
     * Update the LastActivity time to the current.
     */
    void RegisteredClient::UpdateTime() {
        this->LastActivity = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }
    //endregion
    RegisteredClient RegisteredClient::Host={};
}