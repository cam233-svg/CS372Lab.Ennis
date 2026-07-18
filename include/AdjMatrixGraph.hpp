#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include "Graph.hpp"

template <class N>
class AdjMatrixGraph: public Graph<N>  {
private:
	std::vector<N> nodes;
    const static int maxSize = 10;
    short adjMatrix[maxSize][maxSize] = {};
    int numNodes = 0;
    int findNodeInMatrix(N x) const {
        for (int j=0; j < numNodes; ++j)
        {
            if (x == nodes[j])
            {
                return j;
            }
        }
        return -1;
    }
public:
    using Edge = std::pair<N, N>;
	AdjMatrixGraph() = default;

    AdjMatrixGraph(std::vector<N> newNodes, std::vector<Edge> newEdges)
    {
        for (typename std::vector<N>::const_iterator it = newNodes.begin();
             it < newNodes.end();
             ++it)
        {
			numNodes++;
            nodes.push_back(*it);
        }
        for (typename std::vector<pair<N,N>>::const_iterator it = newEdges.begin();
             it < newEdges.end();
             ++it)
        {
            std::pair<N,N> edge = *it;
            int sourceIndex = findNodeInMatrix(edge.first);
            int destIndex = findNodeInMatrix(edge.second);
            if (sourceIndex != -1)
            {
                if (destIndex != -1)
                {
                    adjMatrix[sourceIndex][destIndex] = 1;
                }
            }
        }
    }

    virtual ~AdjMatrixGraph() = default;

    bool adjacent(N x, N y) const override

    {
        bool result = false;
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            short xy = adjMatrix[xIndex][yIndex];
            if (xy == 1) {result = true; };
        }
        return(result);
    }

    std::vector<N>  neighbors(N x) const override
    {
        std::vector<N> v;
        int xIndex = findNodeInMatrix(x);
        if (xIndex != -1)
        {
            for (int i=0; i < numNodes; ++i) {
                if (adjMatrix[xIndex][i] > 0) {
                    v.push_back(nodes[i]);
                }
            }
        }
        return v;
    }
    void addNode(N node) override
    {
        nodes.push_back(node);
        numNodes++;

    }
    void addEdge(N x, N y) override
    {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            adjMatrix[xIndex][yIndex] = 1;
        }
    }

    void deleteEdge(N x, N y) override
    {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        adjMatrix[xIndex][yIndex] = 0;
    }

    std::map<N, N> dfs(N startNode, std::function<void(N)> visit) override
    {
        std::map<N, bool> visited;
        std::map<N, N> parents;

         for (int i = 0; i < numNodes; ++i){
            visited[nodes[i]] = false;
        }
        std::stack<N> s;
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

    std::map<N, N> bfs(N startNode, std::function<void(N)> visit) override
    {
        std::map<N, bool> visited;
        std::map<N, N> parents;
        for (int i = 0; i < numNodes; ++i){
            visited[nodes[i]]= false;
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
