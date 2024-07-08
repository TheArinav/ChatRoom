cmake_minimum_required(VERSION 3.22)
project(ChatRoomServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP src/main.cpp src/Classes/GeneralTypes/ServerAction.cpp src/Classes/GeneralTypes/ServerAction.h src/Classes/Backend/BeckendComms.cpp src/Classes/Backend/BeckendComms.h)
