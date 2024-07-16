//
// Created by ariel on 7/11/2024.
//

#include "Terminal.h"
#include "InstructionInterpreter.h"
#include <iostream>

namespace IO::Terminal{
    void PrintLogo(){
        std::cout << R"(
   ___________________________________________________
  / _________________________________________________ \
 | |        _____  ._.             ._.      ._.      | |
 | |       / ___ \ | |             | |      | |      | |
 | |      | /   \/ | |__.   .___.  | |__.   | |      | |
 | |      | |      | '_. \ /  ^  \ |  __|   | |      | |
 | |      | \___/\ | | | | | (_) | |  |__.  '-'      | |
 | |       \_____/ |_| |_| \___^._\ \____|  [=]      | |
 | |_________________________________________________| |
 | |                                                 | |
 | |   Welcome to the "Chat!" App.                   | |
 | |_________________________________________________| |
 | |                 (c)                             | |
 | |   Copyright 2024   Ariel Ayalon.                | |
 | |_________________________________________________| |
 | |                                                 | |
 | |   Please select an action. For help, type 'h'.  | |
 | |_________________________________________________| |
  \___________________________________________________/

)";
    }
    void clearTerminal() {
        system("clear");
    }

    void StartTerminal(){
        clearTerminal();
        PrintLogo();
        InstructionInterpreter::Setup();

        std::string input;
        while (true) {
            std::cout << "  '---[Enter Instruction]---> ";
            std::getline(std::cin, input);
            if (input == "exit" || input == "q") break;
            else if (input == "cls" || input == "clear") {
                clearTerminal();
                PrintLogo();
                continue;
            }
            auto inst = Instruction{};
            try {
                inst = InstructionInterpreter::Parse( input);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
                continue;
            }


        }
    }

    void WriteOutput(OutputInfo inf, const string& message) {
        //Temporary
        std::cout<< inf.ToString() << message << std::endl;
    }
}