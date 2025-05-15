#include <iostream>
#include <expected>
#include <memory>
#include "graph.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<Graph> graph(nullptr);

    if (argc == 2) {
        if (std::string(argv[1]) == "--generate") {
            auto result = GUI::getGenerate();
            if (!result) {
                std::cerr << "Error: " << result.error() << std::endl;
                return 1;
            }
            graph = std::move(*result);
        }
        else if (std::string(argv[1]) == "--user-provided") {
            auto result = GUI::getUserProvided();
            if (!result) {
                std::cerr << "Error: " << result.error() << std::endl;
                return 1;
            }
            graph = std::move(*result);
        }
        else {
            GUI::HELP::Modes(argv);
            return 1;
        }
    }
    else {
        GUI::HELP::Modes(argv);
        return 1;
    }

    // Main interaction loop
    while (true) {
        auto result = GUI::getAction(graph);
        if (!result) {
            if (result.error() == "quit") {
                break;
            }
            std::cerr << "Error: " << result.error() << std::endl;
        }
    }

    return 0;
}