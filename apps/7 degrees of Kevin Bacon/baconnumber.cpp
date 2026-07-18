#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "AdjListGraph.hpp"

void befriend(Graph<std::string> &g, std::string a, std::string b) {
    g.addEdge(a, b);
    g.addEdge(b, a);
}

void buildSocialGraph(Graph<std::string> &g) {
    std::vector<std::string> people = {
        "Cameron Ennis", "LeBron James", "Stephen Curry", "Kevin Durant",
        "Giannis Antetokounmpo", "Nikola Jokic", "Luka Doncic", "Joel Embiid",
        "Jayson Tatum", "Jimmy Butler", "Damian Lillard", "Anthony Davis",
        "Kawhi Leonard", "Paul George", "Devin Booker", "Ja Morant",
        "Donovan Mitchell", "Zion Williamson", "Trae Young", "Kevin Bacon"
    };
    for (const std::string &person : people) {
        g.addNode(person);
    }

    befriend(g, "Cameron Ennis", "LeBron James");
    befriend(g, "Cameron Ennis", "Stephen Curry");
    befriend(g, "Cameron Ennis", "Kevin Durant");
    befriend(g, "LeBron James", "Giannis Antetokounmpo");
    befriend(g, "LeBron James", "Nikola Jokic");
    befriend(g, "Stephen Curry", "Luka Doncic");
    befriend(g, "Kevin Durant", "Joel Embiid");
    befriend(g, "Giannis Antetokounmpo", "Ja Morant");
    befriend(g, "Giannis Antetokounmpo", "Jayson Tatum");
    befriend(g, "Nikola Jokic", "Jimmy Butler");
    befriend(g, "Luka Doncic", "Damian Lillard");
    befriend(g, "Joel Embiid", "Anthony Davis");
    befriend(g, "Jayson Tatum", "Kawhi Leonard");
    befriend(g, "Jimmy Butler", "Paul George");
    befriend(g, "Damian Lillard", "Devin Booker");
    befriend(g, "Anthony Davis", "Donovan Mitchell");
    befriend(g, "Ja Morant", "Kevin Bacon");

    befriend(g, "Zion Williamson", "Trae Young");
}

bool connectedToBacon(Graph<std::string> &g, std::string start,
                      std::string target, std::vector<std::string> &path) {
    path.clear();

    auto visit = [](std::string) {};
    std::map<std::string, std::string> parents = g.bfs(start, visit);

    if (parents.find(target) == parents.end()) {
        return false;
    }

    std::vector<std::string> backward;
    std::string current = target;
    backward.push_back(current);
    while (current != start) {
        current = parents[current];
        backward.push_back(current);
    }
    for (std::vector<std::string>::reverse_iterator it = backward.rbegin();
         it != backward.rend(); ++it) {
        path.push_back(*it);
    }
    return true;
}

class BaconTest : public ::testing::Test
{
protected:
  AdjListGraph<std::string> social;
  void SetUp() override
  {
    buildSocialGraph(social);
  }

  void TearDown() override
  {
  }
};

TEST_F(BaconTest, CameronIsConnected) {
    std::vector<std::string> path;
    bool connected =
        connectedToBacon(social, "Cameron Ennis", "Kevin Bacon", path);
    EXPECT_TRUE(connected);
    EXPECT_EQ(path.front(), "Cameron Ennis");
    EXPECT_EQ(path.back(), "Kevin Bacon");
}

TEST_F(BaconTest, CameronBaconNumber) {
    std::vector<std::string> path;
    connectedToBacon(social, "Cameron Ennis", "Kevin Bacon", path);
    EXPECT_EQ(path.size(), 5u);
}

TEST_F(BaconTest, HermitNotConnected) {
    std::vector<std::string> path;
    bool connected =
        connectedToBacon(social, "Zion Williamson", "Kevin Bacon", path);
    EXPECT_FALSE(connected);
    EXPECT_TRUE(path.empty());
}

TEST_F(BaconTest, PathIsValid) {
    std::vector<std::string> path;
    connectedToBacon(social, "Cameron Ennis", "Kevin Bacon", path);
    for (std::size_t i = 0; i + 1 < path.size(); ++i) {
        EXPECT_TRUE(social.adjacent(path[i], path[i + 1]));
    }
}
