#include "CircularList.h"
#include <iostream>
#include <string>

static int g_pass = 0;
static int g_fail = 0;
static void check(bool cond, const std::string& name) {
    if (cond) { std::cout << "  [PASS] " << name << "\n"; ++g_pass; }
    else      { std::cout << "  [FAIL] " << name << "\n"; ++g_fail; }
}

struct StringAppender {
    std::string& out;
    void operator()(int& x) { out += std::to_string(x); out += " "; }
};

struct Counter {
    int& n;
    void operator()(int&) { ++n; }
};

static void incrementByOne(int& x) {
    x += 1;
}

static std::string circularOrder(CircularList<int>& cl, int startIndex) {
    std::string s;
    StringAppender app{s};
    cl.traverse(startIndex, app);
    return s;
}

int main() {
    std::cout << "- CircularList test driver -\n";

    CircularList<int> cl;

    cl.push_back(10);
    cl.push_back(20);
    cl.push_back(30);
    cl.push_back(40);
    cl.push_back(50);
    std::cout << "List built via inherited push_back: {10,20,30,40,50}\n";

    std::cout << "1. Circular traversal from different starting points\n";
    check(circularOrder(cl, 0) == "10 20 30 40 50 ",
          "start at index 0 -> 10 20 30 40 50");
    check(circularOrder(cl, 2) == "30 40 50 10 20 ",
          "start at index 2 -> wraps to 30 40 50 10 20");
    check(circularOrder(cl, 4) == "50 10 20 30 40 ",
          "start at last index -> 50 10 20 30 40");

    std::cout << "2. Each element is visited exactly once\n";
    int visits = 0;
    Counter visitCounter{visits};
    cl.traverse(1, visitCounter);
    check(visits == 5, "a circular traversal visits all 5 elements once");

    std::cout << "3. Out-of-range starting index clamps to the head\n";
    check(circularOrder(cl, 99) == "10 20 30 40 50 ",
          "start index past the end behaves like start at 0");

    std::cout << "4. The inherited (base) one-argument traverse still works\n";
    std::string baseOrder;
    StringAppender baseApp{baseOrder};
    cl.traverse(baseApp);
    check(baseOrder == "10 20 30 40 50 ",
          "base List::traverse(doIt) still visits head->tail");

    std::cout << "5. The callback receives T& and may modify elements\n";
    cl.traverse(0, incrementByOne);
    check(circularOrder(cl, 0) == "11 21 31 41 51 ",
          "circular traverse can modify elements through T&");

    std::cout << "6. Circular traversal of an empty list is a safe no-op\n";
    CircularList<int> empty;
    int emptyVisits = 0;
    Counter emptyCounter{emptyVisits};
    empty.traverse(0, emptyCounter);
    check(emptyVisits == 0, "traversing an empty circular list visits nothing");

    std::cout << "-------------------------------------------------------------\n";
    std::cout << "Results: " << g_pass << " passed, " << g_fail << " failed.\n";
    return g_fail == 0 ? 0 : 1;
}
