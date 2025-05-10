#include <iostream>
#include "graph.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    
    // Handle 2-argument commands
    if (argc == 2){
        if(std::string(argv[1]) == "--generate"){
            std::cout << argv[1] << std::endl;
        }
        else if (std::string(argv[1]) == "--user-provided"){
            std::cout << argv[1] << std::endl;
        }
        else {
            GUI::printHelpMsg(argv);
            return 1;
        }
    }
    else if(argc > 2){
        GUI::printHelpMsg(argv);
        return 1;
    }

    return 0;
}