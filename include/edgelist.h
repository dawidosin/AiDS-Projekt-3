#pragma once

#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "graph.h"

class EdgeList : public Graph {
private:
    std::vector<std::pair<int, int>> edges;
    int nodeCount;

public:
    explicit EdgeList(int nodes);

    void print() const override;
    void addEdge(int from, int to) override;
    bool hasEdge(int from, int to) const override;
    std::vector<int> bfs(int start) const override;
    std::vector<int> dfs(int start) const override;
    std::vector<int> getNeighbors(int node) const override;
    int getNodeCount() const override;
    std::vector<std::pair<int, int>> getEdges() const override;
};