#include <vector>
#include <queue>
#include <stack>
#include <functional>

std::vector<int> bfs(int start, int nodeCount, std::function<std::vector<int>(int)> getNeighbors);
std::vector<int> dfs(int start, int nodeCount, std::function<std::vector<int>(int)> getNeighbors);