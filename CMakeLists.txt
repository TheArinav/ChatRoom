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
        src/Classes/Backend/ChatRoomHost.cpp
        src/Classes/Backend/ChatRoomHost.h
        src/Classes/Backend/Server.cpp
        src/Classes/Backend/Server.h
        )

find_package(Threads REQUIRED)
target_link_libraries(CPP PRIVATE Threads::Threads pthread)

# Optional: Set compiler and linker flags explicitly
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
