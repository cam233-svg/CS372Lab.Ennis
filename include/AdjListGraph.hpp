#include "Graph.hpp"
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>
using namespace std;

template <class N>
class AdjListGraph: public Graph<N>  {
private:
    using Edge = std::pair<N, N>;
    using EdgeList = std::list<Edge>;
    std::map<N, EdgeList > vertexMap;
public:
    AdjListGraph() : Graph<N>() { };

    AdjListGraph(const AdjListGraph& other) : Graph<N>() {
        vertexMap = other.vertexMap;
    }

    AdjListGraph& operator= (const AdjListGraph &source) {
        vertexMap = source.vertexMap;
        return *this;
    }

    AdjListGraph(vector<N> newNodes, vector<Edge> newEdgeVec) :
        Graph<N>(newNodes, newEdgeVec) {
        for (const N& node : newNodes) {
            EdgeList nodeEdges;
            for (const Edge& e : newEdgeVec) {
                if (e.first == node) {
                    nodeEdges.push_back(e);
                }
            }
            vertexMap[node] = nodeEdges;
        }
    }

    ~AdjListGraph() = default;

    bool adjacent(N x, N y) const override {
        EdgeList edges = vertexMap.at(x);
        Edge searchEdge{x,y};
        typename EdgeList::const_iterator begin = edges.begin();
        typename EdgeList::const_iterator end = edges.end();
        auto pos = std::find_if(begin,end,
                                [&](Edge const &b) {
            bool match =  (b.first == searchEdge.first
                           && b.second == searchEdge.second);
            return match;
        });
        bool match = false;
        if (pos != end) { match = true; }
        return (match);
    }

    std::vector<N> neighbors(N x) const override {
        std::vector<N> nodes;
        for (const auto& e : vertexMap.at(x)) {
            nodes.push_back(e.second);
        }
        return nodes;
    }

    void addNode(N node) override{
        EdgeList newEdgeList{};
        vertexMap[node] = newEdgeList;
    }

    void addEdge(N x, N y) override {
        Edge forwardEdge{x,y};
        vertexMap[x].push_back(forwardEdge);

    }

    void deleteEdge(N x, N y) override {
        Edge forwardEdge{x,y};
        vertexMap[x].remove(forwardEdge);
    }

    std::map<N, N> dfs(N startNode, std::function<void(N)> visit) override {
        std::map<N, bool> visited;
        std::map<N, N> parents;
        std::stack<N> s;
        for (auto v : vertexMap) {
            visited[v.first] = false;
        }
        s.push(startNode);
        parents[startNode] = startNode;
        while (!s.empty()) {
            N currentNode = s.top();
            s.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            std::vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec ) {
                if (!visited[neighbor]) {
                    parents[neighbor] = currentNode;
                    s.push(neighbor);
                }
            }
        }
        return parents;
    }

    std::map<N, N> bfs(N startNode, std::function<void(N)> visit) override {
        std::map<N, bool> visited;
        std::map<N, N> parents;
        for (auto v: vertexMap) {
            visited[v.first] = false;
        }
        std::queue<N> q;
        q.push(startNode);
        parents[startNode] = startNode;
        while (!q.empty()) {
            N currentNode = q.front();
            q.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            std::vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec) {
                if (!visited[neighbor]) {
                    parents[neighbor] = currentNode;
                    q.push(neighbor);
                }
            }
        }
        return parents;
    }
};
