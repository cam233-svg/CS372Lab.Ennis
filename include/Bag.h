#pragma once

#include <iostream>
#include "Vector.h"

template <typename T>
class Bag {
public:
    Bag() : bagSize(0) {}

    void insert(T item) {
        if (bagSize < items.size()) {
            items.put(item, bagSize);
        } else {
            items.push_back(item);
        }
        bagSize++;
    }

    void remove(T item) {
        for (int i = 0; i < bagSize; i++) {
            if (items.at(i) == item) {
                bagSize--;
                if (i < bagSize) {
                    items.put(items.at(bagSize), i);
                }
                return;
            }
        }
    }

    bool contains(T item) const {
        for (int i = 0; i < bagSize; i++) {
            if (items.at(i) == item) return true;
        }
        return false;
    }

    int size() const { return bagSize; }

    bool isEmpty() const { return bagSize == 0; }

    void traverse() const {
        for (int i = 0; i < bagSize; i++) {
            std::cout << items.at(i) << std::endl;
        }
        std::cout << std::endl;
    }

private:
    Vector<T> items;
    int bagSize;
};