#pragma once
#include "List.h"

template <typename Thing>
class Bag {
private:
    List<Thing> items;
    int  itemCount = 0;
    Thing lastPopped{};

public:
    Bag() = default;

    void insert(Thing aThing) {
        items.push_back(aThing);
        ++itemCount;
    }

    Thing& pop() {
        if (itemCount > 0) {
            lastPopped = items.back();
            items.pop_back();
            --itemCount;
        }
        return lastPopped;
    }

    int size() {
        return itemCount;
    }

    int count() {
        return itemCount;
    }
};
