#include "edgelist.h"

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
    std::vector<int> result;
    if (start < 0 || start >= nodeCount) return result;

    std::vector<std::vector<int>> adjList(nodeCount);
    for (const auto& edge : edges) {
        adjList[edge.first].push_back(edge.second);
    }

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

std::vector<int> EdgeList::dfs(int start) const {
    std::vector<int> result;
    if (start < 0 || start >= nodeCount) return result;

    std::vector<std::vector<int>> adjList(nodeCount);
    for (const auto& edge : edges) {
        adjList[edge.first].push_back(edge.second);
    }

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
