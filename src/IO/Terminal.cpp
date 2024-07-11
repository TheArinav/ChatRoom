//
// Created by ariel on 7/11/2024.
//

#include "Terminal.h"
#include "InstructionInterpreter.h"
#include <iostream>

namespace IO::Terminal{
    void PrintLogo(){
        std::cout << R"(
   __________________________________________________
  /__________________________________________________\
 | |        _____  ._.             ._.      ._.      | |
 | |       /  __ \ | |             | |      | | (TM) | |
 | |      | /   \/ | |__.   .___.  | |__.   | |      | |
 | |      | |      | '_  \ /  ^  \ |  __|   |_|      | |
 | |      | \__ /\ | | | | | (_) | |  |__.           | |
 | |       \_____/ |_| |_| \___^._\ \____|  [=]      | |
 | |                                                 | |
 | |_________________________________________________| |
 | |                                                 | |
 | |   Welcome to the "Chat!" App                    | |
 | |_________________________________________________| |
 | |                 (c)                             | |
 | |   Copyright 2024   Ariel Ayalon                 | |
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
        PrintLogo();
        InstructionInterpreter::Setup();

        std::string input;
        while (true) {
            std::cout << "  > ";
            std::getline(std::cin, input);
            if (input == "exit") break;
            else if (input == "cls" || input == "clear") {
                clearTerminal();
                PrintLogo();
                continue;
            }

            try {

            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    }
}