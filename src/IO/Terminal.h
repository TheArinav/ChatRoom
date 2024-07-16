//
// Created by ariel on 7/11/2024.
//

#ifndef CHATROOMSERVER_TERMINAL_H
#define CHATROOMSERVER_TERMINAL_H

#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <chrono>
#include <ctime>
#include "InstructionInterpreter.h"


using std::vector;
using std::stack;
using std::string;
using std::stringstream;

namespace IO::Terminal{
    /**
     * Keeps track of the context the user is in.
     */
    static stack<Context> ContextStack;
    /**
     * Start the terminal.
     */
    void StartTerminal();
    /**
     * Private method for executing instructions.
     */
    static void ExecuteInstruction();


    enum class OutputSender{
        SERVER_GENERAL,
        SERVER_CHATROOM,
        CLIENT,
        CLIENT_CHATROOM
    };
    enum class OutputType{
        ERROR,
        ERROR_CRITICAL,
        INFO,
        NOTIFICATION
    };
    struct OutputInfo{
        OutputSender Sender;
        OutputType Type;
        time_t TimeReceived;
        OutputInfo(OutputSender sender, OutputType type):
        Sender(sender),Type(type),TimeReceived(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())){};
        string ToString(){
            stringstream ss;
            char buff[20];
            struct tm * timeinfo = localtime(&TimeReceived);
            strftime(buff, sizeof buff, "%d/%b/%y %H:%M",timeinfo);
            string SerializeSender;
            switch (Sender) {

                case OutputSender::SERVER_GENERAL: {
                    SerializeSender = "SERVER";
                    break;
                }
                case OutputSender::SERVER_CHATROOM: {
                    SerializeSender= "SERVER_CHATROOM";
                    break;
                }
                case OutputSender::CLIENT: {
                    SerializeSender= "CLIENT";
                    break;
                }
                case OutputSender::CLIENT_CHATROOM: {
                    SerializeSender= "CLIENT_CHATROOM";
                    break;
                }
            }
            string SerializeType;
            switch (Type) {

                case OutputType::ERROR: {
                    SerializeType = "ERROR";
                    break;
                }
                case OutputType::ERROR_CRITICAL: {
                    SerializeType = "CRITICAL_ERROR";
                    break;
                }
                case OutputType::INFO: {
                    SerializeType = "INFO";
                    break;
                }
                case OutputType::NOTIFICATION: {
                    SerializeType = "NOTIFICATION";
                    break;
                }

            }
            ss << "[" << buff << "]:[" << SerializeSender << "]:[" << SerializeType << "]= ";
            return ss.str();
        }
    };

    void WriteOutput(OutputInfo inf, const string& message);
}

#endif //CHATROOMSERVER_TERMINAL_H
