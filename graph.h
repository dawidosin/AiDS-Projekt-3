#include <vector>

class Graph {
   std::vector<std::vector<int>> vec;

public:
    Graph(int n)
    {
        vec = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    }

    void add_edge(int u, int v)
    {
        vec[u][v] = 1;
        vec[v][u] = 1;
    }
};