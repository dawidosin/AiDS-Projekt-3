#include "algorithms.h"

std::vector<int> bfs(int start, int nodeCount, std::function<std::vector<int>(int)> getNeighbors) {
    std::vector<int> result;
    if (start < 0 || start >= nodeCount) return result;

    std::vector<bool> visited(nodeCount, false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front(); q.pop();
        result.push_back(current);

        for (int neighbor : getNeighbors(current)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return result;
}

std::vector<int> dfs(int start, int nodeCount, std::function<std::vector<int>(int)> getNeighbors) {
    std::vector<int> result;
    if (start < 0 || start >= nodeCount) return result;

    std::vector<bool> visited(nodeCount, false);
    std::stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int current = s.top(); s.pop();

        if (visited[current]) continue;
        visited[current] = true;
        result.push_back(current);

        auto neighbors = getNeighbors(current);
        // Wpychamy w odwrotnej kolejności, aby zachować porządek
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            if (!visited[*it]) {
                s.push(*it);
            }
        }
    }

    return result;
}
