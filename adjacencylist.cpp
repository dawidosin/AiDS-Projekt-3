#include "adjacencylist.h"

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
    std::vector<int> result;
    if (start < 0 || start >= nodeCount) return result;

    std::vector<bool> visited(nodeCount, false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current);

        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return result;
}

std::vector<int> AdjacencyList::dfs(int start) const {
    std::vector<int> result;
    if (start < 0 || start >= nodeCount) return result;

    std::vector<bool> visited(nodeCount, false);
    std::stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (visited[current]) continue;
        visited[current] = true;
        result.push_back(current);

        for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
            if (!visited[*it]) {
                s.push(*it);
            }
        }
    }

    return result;
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
