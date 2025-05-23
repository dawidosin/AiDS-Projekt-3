#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <stdexcept>
#include "graph.h"

class AdjacencyMatrix : public Graph {
private:
    std::vector<std::vector<bool>> matrix;
    int nodeCount;

public:
    explicit AdjacencyMatrix(int nodes);

    void print() const override;
    void addEdge(int from, int to) override;
    bool hasEdge(int from, int to) const override;
    std::vector<int> bfs(int start) const override;
    std::vector<int> dfs(int start) const override;
    std::vector<int> getNeighbors(int node) const override;
    int getNodeCount() const override;
    std::vector<std::pair<int, int>> getEdges() const override;
};

