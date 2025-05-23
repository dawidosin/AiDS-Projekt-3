#pragma once
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <expected>

class Graph {
public:
    enum class Type {matrix, list, table};

    virtual ~Graph() = default;
    virtual void print() const = 0;
    virtual void addEdge(int from, int to) = 0;
    virtual bool hasEdge(int from, int to) const = 0;   
    virtual std::vector<int> bfs(int start) const = 0;
    virtual std::vector<int> dfs(int start) const = 0;
    virtual std::vector<int> getNeighbors(int node) const = 0;
    virtual int getNodeCount() const = 0;
    virtual std::vector<std::pair<int, int>> getEdges() const = 0;

    std::vector<int> kahnTopologicalSort() const;
    std::vector<int> tarjanTopologicalSort() const;

    static std::unique_ptr<Graph> createGraph(const Type type, int nodes, const std::vector<std::vector<int>>& adj);
    static std::unique_ptr<Graph> generateDAG(int nodes, int saturation, Type type);
};