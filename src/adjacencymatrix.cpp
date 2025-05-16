#include "adjacencymatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int nodes)
    : nodeCount(nodes), matrix(nodes, std::vector<bool>(nodes, false)) {}

void AdjacencyMatrix::addEdge(int from, int to) {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        throw std::out_of_range("Invalid node index");
    }
    matrix[from][to] = true;
}

void AdjacencyMatrix::print() const {
    std::cout << "  | ";
    for (int i = 0; i < nodeCount; ++i) std::cout << i << " ";
    std::cout << "\n--+-";
    for (int i = 0; i < nodeCount; ++i) std::cout << "--";
    std::cout << std::endl;

    for (int i = 0; i < nodeCount; ++i) {
        std::cout << i << " | ";
        for (int j = 0; j < nodeCount; ++j) {
            std::cout << (matrix[i][j] ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }
}

bool AdjacencyMatrix::hasEdge(int from, int to) const {
    if (from < 0 || from >= nodeCount || to < 0 || to >= nodeCount) {
        return false;
    }
    return matrix[from][to];
}

std::vector<int> AdjacencyMatrix::bfs(int start) const {
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

        for (int neighbor = 0; neighbor < nodeCount; ++neighbor) {
            if (matrix[current][neighbor] && !visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return result;
}

std::vector<int> AdjacencyMatrix::dfs(int start) const {
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

        for (int neighbor = nodeCount - 1; neighbor >= 0; --neighbor) {
            if (matrix[current][neighbor] && !visited[neighbor]) {
                s.push(neighbor);
            }
        }
    }

    return result;
}

std::vector<int> AdjacencyMatrix::getNeighbors(int node) const {
    std::vector<int> neighbors;
    if (node < 0 || node >= nodeCount) return neighbors;

    for (int i = 0; i < nodeCount; ++i) {
        if (matrix[node][i]) {
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

int AdjacencyMatrix::getNodeCount() const {
    return nodeCount;
}

std::vector<std::pair<int, int>> AdjacencyMatrix::getEdges() const {
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            if (matrix[i][j]) {
                edges.emplace_back(i, j);
            }
        }
    }
    return edges;
}
