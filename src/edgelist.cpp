#include "edgelist.h"
#include "algorithms.h"

EdgeList::EdgeList(int nodes)
    : nodeCount(nodes) {}

void EdgeList::addEdge(int from, int to) {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        throw std::out_of_range("Invalid node index");
    }
    edges.emplace_back(from, to);
}

void EdgeList::print() const {
    for (const auto& edge : edges) {
        std::cout << edge.first << " -> " << edge.second << std::endl;
    }
}

bool EdgeList::hasEdge(int from, int to) const {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        return false;
    }
    return std::find(edges.begin(), edges.end(), std::make_pair(from, to)) != edges.end();
}

std::vector<int> EdgeList::bfs(int start) const {
    return ::bfs(start, nodeCount, [this](int node) { return this->getNeighbors(node); });
}

std::vector<int> EdgeList::dfs(int start) const {
    return ::dfs(start, nodeCount, [this](int node) { return this->getNeighbors(node); });
}

std::vector<int> EdgeList::getNeighbors(int node) const {
    std::vector<int> neighbors;
    if (node < 0 || node >= nodeCount) return neighbors;

    for (const auto& edge : edges) {
        if (edge.first == node) {
            neighbors.push_back(edge.second);
        }
    }

    return neighbors;
}

int EdgeList::getNodeCount() const {
    return nodeCount;
}

std::vector<std::pair<int, int>> EdgeList::getEdges() const {
    return edges;
}
