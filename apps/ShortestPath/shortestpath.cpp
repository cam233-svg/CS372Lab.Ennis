#include "AdjListGraph.hpp"
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
std::vector<int> shortestPath(Graph<T> &aGraph, int start, int destination) {
    aGraph.neighbors(start);
    aGraph.neighbors(destination);

    if (start == destination) {
        return std::vector<int>{start};
    }

    std::queue<int> pending;
    std::map<int, bool> visited;
    std::map<int, int> parent;

    pending.push(start);
    visited[start] = true;

    while (!pending.empty()) {
        int current = pending.front();
        pending.pop();
        std::vector<int> neighVec = aGraph.neighbors(current);
        for (int neighbor : neighVec) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                pending.push(neighbor);
            }
        }
    }

    if (!visited[destination]) {
        return std::vector<int>{};
    }

    std::vector<int> path;
    int node = destination;
    while (node != start) {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

static int g_pass = 0;
static int g_fail = 0;
static void check(bool cond, const string& name) {
    if (cond) { cout << "  [PASS] " << name << "\n"; ++g_pass; }
    else      { cout << "  [FAIL] " << name << "\n"; ++g_fail; }
}

int main() {
    cout << "- Shortest path test driver -\n";

    AdjListGraph<int> g;
    for (int v = 0; v <= 8; ++v) g.addNode(v);

    g.addEdge(0, 3);
    g.addEdge(3, 7);
    g.addEdge(7, 8);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    g.addEdge(4, 8);

    vector<int> p = shortestPath(g, 0, 8);
    check(p == (vector<int>{0, 3, 7, 8}), "shortest path 0 to 8 is 0 3 7 8");

    check(shortestPath(g, 5, 5) == (vector<int>{5}), "start == destination returns single vertex");

    check(shortestPath(g, 8, 0).empty(), "no path returns empty vector");

    bool threw = false;
    try { shortestPath(g, 99, 0); }
    catch (const out_of_range&) { threw = true; }
    check(threw, "out of range start throws std::out_of_range");

    threw = false;
    try { shortestPath(g, 0, 42); }
    catch (const out_of_range&) { threw = true; }
    check(threw, "out of range destination throws std::out_of_range");

    cout << "----------------------------------------------------------------\n";
    cout << "Results: " << g_pass << " passed, " << g_fail << " failed.\n";
    return g_fail == 0 ? 0 : 1;
}
