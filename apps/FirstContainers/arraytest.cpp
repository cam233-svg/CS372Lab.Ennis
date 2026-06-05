#include <iostream>
#include "Array.h"

int main() {
    std::cout << " -- Array<int, 5> -- " << std::endl;
    Array<int, 5> a;
    for (size_t i = 0; i < a.size(); i++) {
        a.put(static_cast<int>(i * 10), i);
    }
    std::cout << "size=" << a.size() << "  capacity=" << a.capacity() << std::endl;
    std::cout << "a.at(2) = " << a.at(2) << std::endl;
    std::cout << "a[4] = " << a[4] << std::endl;
    std::cout << "traverse:" << std::endl;
    a.traverse();

    std::cout << " -- Array<double, 3> -- " << std::endl;
    Array<double, 3> b(3);
    b[0] = 1.1;
    b[1] = 2.2;
    b[2] = 3.3;
    b.traverse();

    std::cout << " -- Array<std::string, 4> -- " << std::endl;
    Array<std::string, 4> c;
    c.put("alpha", 0);
    c.put("bravo",  1);
    c.put("charlie", 2);
    c.put("delta", 3);
    c.traverse();

    return 0;
}
