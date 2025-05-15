#pragma once

#include <iostream>
#include <expected>
#include <memory>
#include <string>
#include "graph.h"

namespace GUI {

    namespace HELP {
        // Displays usage modes for the program
        void Modes(char* argv[]);
        
        // Displays help for graph generation parameters
        void Generate(char* argv[]);
        
        // Displays available actions in interactive mode
        void Action(char* argv[]);
    }

    // Gets graph generation parameters from user and returns a Graph
    // Returns an error message if input is invalid
    std::expected<std::unique_ptr<Graph>, std::string> getGenerate();
    std::expected<std::unique_ptr<Graph>, std::string> getUserProvided();

    // Gets and executes an action from the user
    // Returns an error message if action is invalid
    // Takes the graph as a parameter to perform actions on it
    std::expected<void, std::string> getAction(std::unique_ptr<Graph>& graph);
}