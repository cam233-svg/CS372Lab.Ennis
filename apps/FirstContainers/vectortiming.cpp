#include <iostream>
#include <chrono>
#include "Vector.h"
#include "VectorSTLCopy.h"
#include "VectorLarge.h"

void timeInsertions(Vector<int>* v, int n, const std::string& label) {
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        v->push_back(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration<double, std::milli>(end - start);
    std::cout << label << "  n=" << n
              << "  time=" << elapsed.count() << " ms\n";
}

int main() {
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    std::cout << " -- Vector (for-loop copy) -- " << std::endl;
    for (int s = 0; s < numSizes; s++) {
        Vector<int> v;
        timeInsertions(&v, sizes[s], "Vector      ");
    }

    std::cout << "\n -- VectorSTLCopy (std::copy) -- " << std::endl;
    for (int s = 0; s < numSizes; s++) {
        VectorSTLCopy<int> v;
        timeInsertions(&v, sizes[s], " -- VectorSTLCopy -- ");
    }

    std::cout << "\n -- VectorLarge (start=128, growth=4x) -- " << std::endl;
    for (int s = 0; s < numSizes; s++) {
        VectorLarge<int> v;
        timeInsertions(&v, sizes[s], " -- VectorLarge -- ");
    }

    return 0;
}
