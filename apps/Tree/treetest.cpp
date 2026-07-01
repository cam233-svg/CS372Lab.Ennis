#include "Tree.h"
#include <iostream>
#include <string>

static int g_pass = 0;
static int g_fail = 0;
static void check(bool cond, const std::string& name) {
    if (cond) { std::cout << "  [PASS] " << name << "\n"; ++g_pass; }
    else      { std::cout << "  [FAIL] " << name << "\n"; ++g_fail; }
}

struct Appender {
    std::string& out;
    void operator()(int x) { out += std::to_string(x); out += " "; }
};

static std::string* g_sink = nullptr;
static void appendFn(int x) { *g_sink += std::to_string(x); *g_sink += " "; }

static Tree<int> leaf(int v) { return Tree<int>(Tree<int>(), v, Tree<int>()); }

static Tree<int> makeTree() {
    Tree<int> left  (leaf(1), 2, leaf(3));
    Tree<int> right (leaf(5), 6, leaf(7));
    return Tree<int>(left, 4, right);
}

static void testStructure() {
    std::cout << "1. Tree structure and DFS traversals\n";
    Tree<int> t = makeTree();
    check(!t.isEmpty(),   "built tree is not empty");
    check(t.size() == 7,  "size() counts all seven nodes");
    check(t.root() == 4,  "root() is 4");

    std::string in;   Appender inApp{in};   t.inorder(inApp);
    check(in == "1 2 3 4 5 6 7 ", "inorder yields sorted order");

    std::string pre;  Appender preApp{pre}; t.preorder(preApp);
    check(pre == "4 2 1 3 6 5 7 ", "preorder visits root before children");
}

static void testParentPointers() {
    std::cout << "2. Parent pointers\n";
    Tree<int> t = makeTree();

    check(t.parent().isEmpty(), "root's parent is null (empty tree)");

    Tree<int> l = t.left();
    check(l.root() == 2, "left child is 2");
    check(l.parent().root() == 4, "parent of 2 is 4");

    Tree<int> r = t.right();
    check(r.parent().root() == 4, "parent of 6 is 4");

    Tree<int> leaf1 = t.left().left();
    check(leaf1.root() == 1, "deepest-left node is 1");
    check(leaf1.parent().root() == 2, "parent of 1 is 2");
}

static void testLevelTraversal() {
    std::cout << "3. Standalone recursive level (breadth-first) traversal\n";
    Tree<int> t = makeTree();

    std::string byFunctor;
    Appender app{byFunctor};
    levelTraversal(t, app);
    check(byFunctor == "4 2 6 1 3 5 7 ",
          "level order is root, then level 1, then level 2");

    std::string byFnPtr;
    g_sink = &byFnPtr;
    levelTraversal(t, appendFn);
    check(byFnPtr == "4 2 6 1 3 5 7 ", "level traversal accepts a function pointer");

    int sum = 0;
    levelTraversal(t, [&sum](int x) { sum += x; });
    check(sum == 28, "level traversal accepts a lambda (sum 1..7 == 28)");

    int calls = 0;
    Tree<int> empty;
    levelTraversal(empty, [&calls](int) { ++calls; });
    check(calls == 0, "level traversal of an empty tree visits nothing");
}

static void testPrune() {
    std::cout << "4. Standalone recursive prune (drop original leaves)\n";
    Tree<int> t = makeTree();
    Tree<int> p = prune(t);

    check(p.size() == 3, "pruned tree has 3 nodes (leaves 1,3,5,7 removed)");
    check(p.root() == 4, "pruned root is still 4");

    std::string lvl;
    Appender app{lvl};
    levelTraversal(p, app);
    check(lvl == "4 2 6 ", "pruned tree is just 4 with children 2 and 6");

    check(p.left().left().isEmpty() && p.left().right().isEmpty(),
          "node 2 is now a leaf in the pruned tree");

    check(t.size() == 7, "original tree is unchanged after prune");

    check(prune(leaf(99)).isEmpty(), "pruning a lone leaf gives an empty tree");

    check(prune(Tree<int>()).isEmpty(), "pruning an empty tree gives an empty tree");
}

int main() {
    std::cout << "- Tree test driver -\n";
    testStructure();
    testParentPointers();
    testLevelTraversal();
    testPrune();
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Results: " << g_pass << " passed, " << g_fail << " failed.\n";
    return g_fail == 0 ? 0 : 1;
}
