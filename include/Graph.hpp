#pragma once
#include <vector>
#include <utility>
#include <functional>
#include <map>
template <class N>
class Graph {
public:
    using Edge = std::pair<N, N>;
    Graph() = default;
    Graph(std::vector<N> nodes, std::vector<Edge> edges) {};
    virtual ~Graph() = default;

    virtual bool adjacent(N x, N y) const = 0;
    virtual std::vector<N> neighbors(N x) const = 0;
    virtual void addNode(N x) = 0;
    virtual void addEdge(N x, N y) = 0;
    virtual void deleteEdge(N x, N y) = 0;
    virtual std::map<N, N> dfs(N startNode, std::function<void(N)> visit) = 0;
    virtual std::map<N, N> bfs(N startNode, std::function<void(N)> visit) = 0;
};
