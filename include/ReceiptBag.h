#pragma once

#include <iostream>
#include "Vector.h"

template <typename T>
class ReceiptBag {
public:
    ReceiptBag() : count(0), nextReceipt(0) {}

    int insert(T item) {
        int receipt = nextReceipt++;
        if (count < items.size()) {
            items.put(item, count);
            receipts.put(receipt, count);
        } else {
            items.push_back(item);
            receipts.push_back(receipt);
        }
        count++;
        return receipt;
    }

    T& remove(int receipt) {
        for (int i = 0; i < count; i++) {
            if (receipts.at(i) == receipt) {
                lastRemoved = items.at(i);
                count--;
                if (i < count) {
                    items.put(items.at(count), i);
                    receipts.put(receipts.at(count), i);
                }
                return lastRemoved;
            }
        }
        std::cerr << "ReceiptBag::remove: receipt not found\n";
        exit(1);
    }

    bool hasReceipt(int receipt) const {
        for (int i = 0; i < count; i++) {
            if (receipts.at(i) == receipt) return true;
        }
        return false;
    }

    int size() const { return count; }

    bool isEmpty() const { return count == 0; }

    void traverse() const {
        for (int i = 0; i < count; i++) {
            std::cout << "receipt=" << receipts.at(i)
                      << " item=" << items.at(i) << std::endl;
        }
        std::cout << std::endl;
    }

private:
    Vector<T> items;
    Vector<int> receipts;
    T lastRemoved;
    int count;
    int nextReceipt;
};
