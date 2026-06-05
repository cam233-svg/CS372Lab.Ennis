#include <iostream>
#include "Bag.h"
#include "ReceiptBag.h"

void testBag() {
    std::cout << " -- Bag Tests -- " << std::endl;
    Bag<int> b;

    std::cout << "isEmpty: " << (b.isEmpty() ? "true" : "false") << std::endl;

    b.insert(10);
    b.insert(20);
    b.insert(30);
    b.insert(20);

    std::cout << "size after 4 inserts: " << b.size() << std::endl;
    std::cout << "contains(20): " << (b.contains(20) ? "true" : "false") << std::endl;
    std::cout << "contains(99): " << (b.contains(99) ? "true" : "false") << std::endl;

    std::cout << "traverse before remove:" << std::endl;
    b.traverse();

    b.remove(20);
    std::cout << "size after removing 20 once: " << b.size() << std::endl;
    std::cout << "contains(20) after one remove: " << (b.contains(20) ? "true" : "false") << std::endl;

    b.remove(10);
    b.remove(30);
    b.remove(20);
    std::cout << "isEmpty after removing all: " << (b.isEmpty() ? "true" : "false") << std::endl;
}

void testReceiptBag() {
    std::cout << "\n -- ReceiptBag Tests -- " << std::endl;
    ReceiptBag<std::string> rb;

    std::cout << "isEmpty: " << (rb.isEmpty() ? "true" : "false") << std::endl;

    int r1 = rb.insert("apple");
    int r2 = rb.insert("pineapple");
    int r3 = rb.insert("watermelon");
    int r4 = rb.insert("date");

    std::cout << "receipts: r1=" << r1 << " r2=" << r2
              << " r3=" << r3 << " r4=" << r4 << std::endl;
    std::cout << "size after 4 inserts: " << rb.size() << std::endl;

    std::cout << "traverse after inserts:" << std::endl;
    rb.traverse();

    std::cout << "hasReceipt(r2): " << (rb.hasReceipt(r2) ? "true" : "false") << std::endl;

    std::string& removed = rb.remove(r2);
    std::cout << "removed by receipt r2: " << removed << std::endl;
    std::cout << "size after remove: " << rb.size() << std::endl;
    std::cout << "hasReceipt(r2) after remove: " << (rb.hasReceipt(r2) ? "true" : "false") << std::endl;

    std::cout << "traverse after remove:" << std::endl;
    rb.traverse();

    std::string& removed2 = rb.remove(r1);
    std::cout << "removed by receipt r1: " << removed2 << std::endl;

    std::string& removed3 = rb.remove(r4);
    std::cout << "removed by receipt r4: " << removed3 << std::endl;

    std::string& removed4 = rb.remove(r3);
    std::cout << "removed by receipt r3: " << removed4 << std::endl;

    std::cout << "isEmpty after removing all: " << (rb.isEmpty() ? "true" : "false") << std::endl;

    std::cout << "\n -- ReceiptBag<int> Test -- " << std::endl;
    ReceiptBag<int> ri;
    int ra = ri.insert(100);
    int rb2 = ri.insert(200);
    int rc = ri.insert(300);
    std::cout << "receipts: " << ra << " " << rb2 << " " << rc << std::endl;
    int& val = ri.remove(rb2);
    std::cout << "removed receipt " << rb2 << " -> value=" << val << std::endl;
    ri.traverse();
}

int main() {
    testBag();
    testReceiptBag();
    return 0;
}
