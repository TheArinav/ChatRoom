cmake_minimum_required(VERSION 3.22)

project(ChatRoomServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(ChatApp
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
        src/Classes/Backend/ChatRoomHost.cpp
        src/Classes/Backend/ChatRoomHost.h
        src/Classes/Backend/Server.cpp
        src/Classes/Backend/Server.h
        src/Classes/Frontend/Account.cpp
        src/Classes/Frontend/Account.h
        src/Classes/GeneralTypes/ClientAction.cpp
        src/Classes/GeneralTypes/ClientAction.h
        src/IO/Terminal.cpp src/IO/Terminal.h src/IO/InstructionInterpreter.cpp src/IO/InstructionInterpreter.h)

find_package(Threads REQUIRED)
target_link_libraries(ChatApp PRIVATE Threads::Threads pthread)

# Optional: Set compiler and linker flags explicitly
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
