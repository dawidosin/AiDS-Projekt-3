#include "gui.h"
#include "graph.h"
#include "adjacencylist.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace GUI;

void HELP::Modes(char* argv[]) {
    std::cerr << "Usage options:\n";
    std::cerr << "  " << argv[0] << " --generate       Generate a random acyclic graph\n";
    std::cerr << "  " << argv[0] << " --user-provided  Provide your own graph values\n";
}

void HELP::Generate(char* argv[]) {
    std::cerr << "\nGraph Generation Parameters:\n";
    std::cerr << "  nodes>       Number of nodes (1-100)\n";
    std::cerr << "  saturation>  Edge saturation percentage (1-100)\n";
}

void HELP::Action(char* argv[]) {
    std::cerr << "\nAvailable Actions:\n";
    std::cerr << "  Print               - Print graph structure\n";
    std::cerr << "  BFS <node>          - Breadth-First Search from node\n";
    std::cerr << "  DFS <node>          - Depth-First Search from node\n";
    std::cerr << "  Find <from> <to>    - Check if edge exists\n";
    std::cerr << "  TopoSort [kahn|tarjan] - Topological sort\n";
    std::cerr << "  Help                - Show this help\n";
    std::cerr << "  Quit                - Exit program\n";
}

std::expected<std::unique_ptr<Graph>, std::string> GUI::getGenerate() {
    int nodes, saturation;
    Graph::Type type;

    std::string input;
    std::cout << "type> ";
    std::cin >> input;
    if (input == "list") type = Graph::Type::list;
    else if (input == "matrix") type = Graph::Type::matrix;
    else if (input == "table") type = Graph::Type::table;
    else {
        return std::unexpected("Invalid graph type");
    }
    
    std::cout << "nodes> ";
    if (!(std::cin >> nodes) || nodes < 1 || nodes > 100) {
        return std::unexpected("Invalid node count. Must be between 1-100.");
    }

    std::cout << "saturation> ";
    if (!(std::cin >> saturation) || saturation < 1 || saturation > 100) {
        return std::unexpected("Invalid saturation. Must be between 1-100.");
    }

    try {
        return Graph::generateDAG(nodes, saturation, type);
    } catch (const std::exception& e) {
        return std::unexpected(std::string("Graph generation failed: ") + e.what());
    }
}

std::expected<std::unique_ptr<Graph>, std::string> GUI::getUserProvided() {
    int nodeCount;
    std::cout << "nodes> ";
    if (!(std::cin >> nodeCount) || nodeCount <= 0) {
        return std::unexpected("Invalid number of nodes");
    }

    auto graph = std::make_unique<AdjacencyList>(nodeCount);
    std::cin.ignore();

    for (int from = 1; from <= nodeCount; ++from) {
        std::string line;
        std::cout << std::to_string(from) << "> ";
        std::getline(std::cin, line);

        std::istringstream iss(line);
        int to;
        while (iss >> to) {
            if (to < 1 || to > nodeCount) {
                return std::unexpected("Invalid node number: " + std::to_string(to));
            }
            graph->addEdge(from - 1, to - 1);
        }
    }

    return graph;
}

std::expected<void, std::string> GUI::getAction(std::unique_ptr<Graph>& graph) {
    std::string input;
    std::cout << "action> ";
    std::getline(std::cin >> std::ws, input);
    
    std::istringstream iss(input);
    std::string command;
    iss >> command;

    if (input == "Print") {
        graph->print();
    }
    else if (input == "Breath-first search") {
        int start;
        if (!(iss >> start)) {
            return std::unexpected("Missing start node for BFS");
        }
        auto result = graph->bfs(start);
        std::cout << "BFS: ";
        for (int node : result) std::cout << node << " ";
        std::cout << "\n";
    }
    else if (input == "Depth-first search") {
        int start;
        if (!(iss >> start)) {
            return std::unexpected("Missing start node for DFS");
        }
        auto result = graph->dfs(start);
        std::cout << "DFS: ";
        for (int node : result) std::cout << node << " ";
        std::cout << "\n";
    }
    else if (input == "Find") {
        int from, to;
        if (!(iss >> from >> to)) {
            return std::unexpected("Missing nodes for Find");
        }
        std::cout << "Edge " << from << "->" << to << " " 
                  << (graph->hasEdge(from, to) ? "exists" : "does not exist") << "\n";
    }
    else if (input == "TopoSort") {
        std::string method;
        iss >> method;
        std::vector<int> result;
        
        if (method.empty() || method == "kahn") {
            result = graph->kahnTopologicalSort();
        } 
        else if (method == "tarjan") {
            result = graph->tarjanTopologicalSort();
        } 
        else {
            return std::unexpected("Invalid topological sort method");
        }

        std::cout << "Topological Sort: ";
        for (int node : result) std::cout << node << " ";
        std::cout << "\n";
    }
    else if (input == "Help") {
        HELP::Action(nullptr);
    }
    else if (input == "Quit") {
        return std::unexpected("quit");
    }
    else {
        return std::unexpected("Unknown command. Type 'Help' for options.");
    }

    return {};
}