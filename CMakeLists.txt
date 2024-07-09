cmake_minimum_required(VERSION 3.22)

project(ChatRoomServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP
        src/main.cpp
        src/Classes/GeneralTypes/ServerAction.cpp
        src/Classes/GeneralTypes/ServerAction.h
        src/Classes/Backend/BackendComms.cpp
        src/Classes/Backend/BackendComms.h
        src/Classes/Backend/RegisteredClient.cpp
        src/Classes/Backend/RegisteredClient.h
        src/Classes/GeneralTypes/MessageQueue.cpp
        src/Classes/GeneralTypes/MessageQueue.h
        src/Classes/GeneralTypes/Message.cpp
        src/Classes/GeneralTypes/Message.h
)
