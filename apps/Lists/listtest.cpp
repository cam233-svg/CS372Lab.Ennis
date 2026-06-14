#include "List.h"
#include "Bag1.h"
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

static std::string toString(List<int>& l) {
    std::string s;
    StringAppender app{s};
    l.traverse(app);
    return s;
}

static int countElems(List<int>& l) {
    int n = 0;
    Counter c{n};
    l.traverse(c);
    return n;
}

static List<int> makeList(int a, int b, int c) {
    List<int> l;
    l.push_back(a);
    l.push_back(b);
    l.push_back(c);
    return l;
}

static void testBasics() {
    std::cout << "1. Basic List operations\n";
    List<int> l;
    check(l.empty(), "new list is empty");

    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    check(!l.empty(),                 "list not empty after push_back");
    check(countElems(l) == 3,         "three elements after three push_back");
    check(l.front() == 10,            "front() is first pushed_back");
    check(l.back() == 30,             "back() is last pushed_back");

    l.push_front(5);
    check(l.front() == 5,             "push_front updates front()");
    check(toString(l) == "5 10 20 30 ", "traverse visits head->tail in order");

    l.pop_front();
    check(l.front() == 10,            "pop_front removes the head");
    l.pop_back();
    check(l.back() == 20,             "pop_back removes the tail");
    check(toString(l) == "10 20 ",    "list is {10,20} after pops");

    List<int> one(42);
    check(one.front() == 42 && one.back() == 42 && countElems(one) == 1,
          "List(T) builds a one-element list");
}

static void testCopy() {
    std::cout << "2. Copy constructor / copy assignment (deep copy)\n";
    List<int> a;
    a.push_back(1); a.push_back(2); a.push_back(3);

    List<int> b(a);
    check(toString(b) == "1 2 3 ", "copy constructor reproduces contents");

    a.front() = 99;
    check(a.front() == 99 && b.front() == 1,
          "modifying original does not affect the copy (deep copy)");

    List<int> c;
    c.push_back(7);
    c = a;
    check(toString(c) == "99 2 3 ", "copy assignment reproduces contents");
    a.push_back(4);
    check(countElems(a) == 4 && countElems(c) == 3,
          "copy-assigned list is independent of the source");

    c = c;
    check(toString(c) == "99 2 3 ", "self copy-assignment leaves list intact");
}

static void testMove() {
    std::cout << "3. Move constructor / move assignment\n";

    List<int> b = makeList(1, 2, 3);
    check(toString(b) == "1 2 3 ", "construct a list from a returned temporary");

    List<int> d;
    d.push_back(100);
    d = makeList(8, 9, 0);
    check(toString(d) == "8 9 0 ", "assign a returned temporary over an existing list");
}

static void testReferenceOverloads() {
    std::cout << "4. Reference vs const-reference overloads of front()/back()\n";

    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);

    l.front() = 111;
    l.back()  = 333;
    check(l.front() == 111, "writing through front() reference modifies the element");
    check(l.back()  == 333, "writing through back() reference modifies the element");

    int& ref = l.front();
    ref = 222;
    check(l.front() == 222, "named int& from front() aliases the stored element");

    const List<int>& cref = l;
    check(cref.front() == 222, "const front() overload reads the element");
    check(cref.back()  == 333, "const back() overload reads the element");
}

static void testBag() {
    std::cout << "5. Bag<Thing> backed by a List\n";
    Bag<int> bag;
    check(bag.size() == 0 && bag.count() == 0, "new bag is empty");

    bag.insert(1);
    bag.insert(2);
    bag.insert(3);
    check(bag.size() == 3,  "size() counts inserted items");
    check(bag.count() == 3, "count() agrees with size()");

    int popped = bag.pop();
    check(popped == 3,      "pop() returns an item from the bag");
    check(bag.size() == 2,  "size() drops after pop()");

    int& r = bag.pop();
    check(r == 2,           "pop() hands back a usable Thing& reference");
    check(bag.size() == 1,  "size() drops again after second pop()");

    bag.pop();
    check(bag.size() == 0,  "bag is empty after popping every item");
}

int main() {
    std::cout << "- List / Bag test driver -\n";
    testBasics();
    testCopy();
    testMove();
    testReferenceOverloads();
    testBag();
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Results: " << g_pass << " passed, " << g_fail << " failed.\n";
    return g_fail == 0 ? 0 : 1;
}
