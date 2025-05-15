#include "graph.h"
#include "adjacencymatrix.h"
#include "adjacencylist.h"
#include "edgelist.h"
#include <queue>
#include <expected>
#include <algorithm>
#include <random>

std::unique_ptr<Graph> Graph::createGraph(const Type type, int nodes, const std::vector<std::vector<int>>& adj) {
    std::unique_ptr<Graph> graph;
    
    if (type == Type::matrix) {
        graph = std::make_unique<AdjacencyMatrix>(nodes);
    } else if (type == Type::list) {
        graph = std::make_unique<AdjacencyList>(nodes);
    } else if (type == Type::table) {
        graph = std::make_unique<EdgeList>(nodes);
    } else {
        throw std::invalid_argument("Unknown graph type");
    }

    for (int from = 0; from < static_cast<int>(adj.size()); ++from) {
        for (int to : adj[from]) {
            graph->addEdge(from, to);
        }
    }

    return graph;
}

std::vector<int> Graph::kahnTopologicalSort() const {
    int n = getNodeCount();
    std::vector<int> inDegree(n, 0), result;

    for (int i = 0; i < n; ++i) {
        for (int neighbor : getNeighbors(i)) {
            inDegree[neighbor]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int current = q.front(); q.pop();
        result.push_back(current);

        for (int neighbor : getNeighbors(current)) {
            if (--inDegree[neighbor] == 0) q.push(neighbor);
        }
    }

    if (result.size() != static_cast<size_t>(n)) {
        throw std::runtime_error("Graph has at least one cycle");
    }

    return result;
}

void tarjanVisit(int node, const Graph& graph, std::vector<bool>& perm, std::vector<bool>& temp, std::vector<int>& result) {
    if (perm[node]) return;
    if (temp[node]) throw std::runtime_error("Graph has at least one cycle");

    temp[node] = true;
    for (int neighbor : graph.getNeighbors(node)) {
        tarjanVisit(neighbor, graph, perm, temp, result);
    }
    temp[node] = false;
    perm[node] = true;
    result.push_back(node);
}

std::vector<int> Graph::tarjanTopologicalSort() const {
    int n = getNodeCount();
    std::vector<bool> perm(n, false), temp(n, false);
    std::vector<int> result;

    for (int i = 0; i < n; ++i) {
        if (!perm[i]) {
            tarjanVisit(i, *this, perm, temp, result);
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::unique_ptr<Graph> Graph::generateDAG(int nodes, int saturation, Type type) {
    if (nodes < 1) throw std::invalid_argument("Number of nodes must be positive");
    if (saturation < 0 || saturation > 100) {
        throw std::invalid_argument("Saturation must be between 0 and 100");
    }

    std::unique_ptr<Graph> graph;
    switch (type) {
        case Type::matrix:
            graph = std::make_unique<AdjacencyMatrix>(nodes);
            break;
        case Type::list:
            graph = std::make_unique<AdjacencyList>(nodes);
            break;
        case Type::table:
            graph = std::make_unique<EdgeList>(nodes);
            break;
        default:
            throw std::invalid_argument("Unsupported graph type");
    }

    int maxPossibleEdges = nodes * (nodes - 1) / 2;
    int targetEdges = maxPossibleEdges * saturation / 100;

    std::vector<std::pair<int, int>> allPossibleEdges;
    for (int i = 0; i < nodes; ++i) {
        for (int j = i + 1; j < nodes; ++j) {
            allPossibleEdges.emplace_back(i, j);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allPossibleEdges.begin(), allPossibleEdges.end(), g);

    for (int i = 0; i < std::min(static_cast<int>(allPossibleEdges.size()), targetEdges); ++i) {
        graph->addEdge(allPossibleEdges[i].first, allPossibleEdges[i].second);
    }

    // Ensure at least one edge exists if saturation > 0
    if (targetEdges > 0 && graph->getEdges().empty()) {
        graph->addEdge(0, 1);
    }

    return graph;
}