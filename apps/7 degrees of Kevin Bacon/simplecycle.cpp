#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include "AdjListGraph.hpp"

bool isSimpleCycle(std::vector<int> path, Graph<int> &g) {
    if (path.size() < 2) {
        return false;
    }

    if (path.front() != path.back()) {
        return false;
    }

    for (std::size_t i = 0; i + 1 < path.size(); ++i) {
        int currentNode = path[i];
        int nextNode = path[i + 1];
        std::vector<int> neighVec = g.neighbors(currentNode);
        std::vector<int>::iterator fIter =
            std::find(neighVec.begin(), neighVec.end(), nextNode);
        if (fIter == neighVec.end()) {
            return false;
        }
    }

    std::vector<int> seen;
    for (std::size_t i = 0; i + 1 < path.size(); ++i) {
        int node = path[i];
        if (std::find(seen.begin(), seen.end(), node) != seen.end()) {
            return false;
        }
        seen.push_back(node);
    }

    return true;
}

class SimpleCycleTest : public ::testing::Test
{
protected:
  AdjListGraph<int> testALG;
  void SetUp() override
  {
    testALG.addNode(0);
    testALG.addNode(1);
    testALG.addNode(2);
    testALG.addNode(3);

    testALG.addEdge(0, 1);
    testALG.addEdge(0, 2);
    testALG.addEdge(0, 3);

    testALG.addEdge(1, 0);
    testALG.addEdge(1, 2);
    testALG.addEdge(1, 3);

    testALG.addEdge(2, 0);
    testALG.addEdge(2, 1);
    testALG.addEdge(2, 3);

    testALG.addEdge(3, 0);
    testALG.addEdge(3, 1);
    testALG.addEdge(3, 2);
  }

  void TearDown() override
  {
  }
};

TEST_F(SimpleCycleTest, ShortCycle) {
    std::vector<int> path{0, 1, 2, 0};
    EXPECT_TRUE(isSimpleCycle(path, testALG));
}

TEST_F(SimpleCycleTest, FullCycle) {
    std::vector<int> path{0, 1, 2, 3, 0};
    EXPECT_TRUE(isSimpleCycle(path, testALG));
}

TEST_F(SimpleCycleTest, NotClosed) {
    std::vector<int> path{0, 1, 2, 3};
    EXPECT_FALSE(isSimpleCycle(path, testALG));
}

TEST_F(SimpleCycleTest, RepeatsNode) {
    std::vector<int> path{0, 1, 3, 1, 0};
    EXPECT_FALSE(isSimpleCycle(path, testALG));
}

TEST_F(SimpleCycleTest, InvalidEdge) {
    testALG.deleteEdge(1, 2);
    std::vector<int> path{0, 1, 2, 0};
    EXPECT_FALSE(isSimpleCycle(path, testALG));
}
