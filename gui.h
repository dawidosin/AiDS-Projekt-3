#include <iostream>

namespace GUI{
    void printHelpMsg(char* argv[]){
        std::cerr << "Usage options:\n";
        std::cerr << "  " << argv[0] << " --generate           Generate a random acyclic graph\n";
        std::cerr << "  " << argv[0] << " --user-provided      Provide your own graph values\n";
    }
}