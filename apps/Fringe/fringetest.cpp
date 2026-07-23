#include "Tree.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

static int g_pass = 0;
static int g_fail = 0;
static void check(bool cond, const string& name) {
    if (cond) { cout << "  [PASS] " << name << "\n"; ++g_pass; }
    else      { cout << "  [FAIL] " << name << "\n"; ++g_fail; }
}

static Tree<int> leaf(int v) { return Tree<int>(Tree<int>(), v, Tree<int>()); }

int main() {
    cout << "- Fringe test driver -\n";

    Tree<int> a(
        Tree<int>(leaf(1), 2, leaf(3)),
        4,
        Tree<int>(leaf(5), 6, leaf(7)));

    Tree<int> b(
        leaf(1),
        2,
        Tree<int>(leaf(3), 4, Tree<int>(leaf(5), 6, leaf(7))));

    Tree<int> c(
        Tree<int>(leaf(1), 2, leaf(3)),
        4,
        Tree<int>(leaf(5), 6, leaf(8)));

    list<int> fa = fringe(a);
    list<int> expected{1, 3, 5, 7};
    check(fa == expected, "fringe of a is 1 3 5 7 left-to-right");

    check(hasSameFringe(a, b), "a and b have same fringe despite different shapes");
    check(!hasSameFringe(a, c), "a and c have different fringe");

    check(fringe(leaf(9)) == list<int>{9}, "fringe of a lone leaf is that leaf");
    check(fringe(Tree<int>()).empty(), "fringe of an empty tree is empty");

    cout << "----------------------------------------------------------------\n";
    cout << "Results: " << g_pass << " passed, " << g_fail << " failed.\n";
    return g_fail == 0 ? 0 : 1;
}
