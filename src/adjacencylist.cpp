#include "adjacencylist.h"
#include "algorithms.h"

AdjacencyList::AdjacencyList(int nodes) : nodeCount(nodes), adjList(nodes) {}

void AdjacencyList::addEdge(int from, int to) {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        throw std::out_of_range("Invalid node index");
    }
    adjList[from].push_back(to);
}

void AdjacencyList::print() const {
    for (int i = 0; i < nodeCount; ++i) {
        std::cout << i << " | ";
        for (int neighbor : adjList[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

bool AdjacencyList::hasEdge(int from, int to) const {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        return false;
    }
    return std::find(adjList[from].begin(), adjList[from].end(), to) != adjList[from].end();
}

std::vector<int> AdjacencyList::bfs(int start) const {
    return ::bfs(start, nodeCount, [this](int node) { return this->getNeighbors(node); });
}

std::vector<int> AdjacencyList::dfs(int start) const {
    return ::dfs(start, nodeCount, [this](int node) { return this->getNeighbors(node); });
}

std::vector<int> AdjacencyList::getNeighbors(int node) const {
    if (node < 0 || node >= nodeCount) return {};
    return adjList[node];
}

int AdjacencyList::getNodeCount() const {
    return nodeCount;
}

std::vector<std::pair<int, int>> AdjacencyList::getEdges() const {
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < nodeCount; ++i) {
        for (int neighbor : adjList[i]) {
            edges.emplace_back(i, neighbor);
        }
    }
    return edges;
}
