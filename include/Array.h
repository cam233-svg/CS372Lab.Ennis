#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cstddef>

template <typename T, size_t N>
class Array {
public:
    Array() {}

    Array(size_t n) {
        (void)n;
    }

    void put(T data, size_t index) {
        if (index >= N) {
            std::cerr << "Array::put: index out of bounds\n";
            exit(1);
        }
        arr[index] = data;
    }

    T& at(size_t index) {
        if (index >= N) {
            std::cerr << "Array: index out of bounds on access" << std::endl;
            exit(1);
        }
        return arr[index];
    }

    const T& at(size_t index) const {
        if (index >= N) {
            std::cerr << "Array: index out of bounds on access" << std::endl;
            exit(1);
        }
        return arr[index];
    }

    size_t size() const { return N; }

    size_t capacity() const { return N; }

    void traverse() const {
        for (size_t i = 0; i < N; i++) {
            std::cout << arr[i] << std::endl;
        }
        std::cout << std::endl;
    }

    T& operator[](size_t i) {
        if (i >= N) {
            std::cerr << std::endl << "Array index out of bounds" << std::endl;
            exit(1);
        }
        return arr[i];
    }

    const T& operator[](size_t i) const {
        if (i >= N) {
            std::cerr << std::endl << "Array index out of bounds" << std::endl;
            exit(1);
        }
        return arr[i];
    }

private:
    T arr[N];
};

#endif
