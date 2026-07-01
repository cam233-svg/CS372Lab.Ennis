#pragma once
#include "List.h"
#include <functional>

template <typename T>
class CircularList : public List<T> {
public:
    using List<T>::traverse;

    void traverse(int startIndex, std::function<void(T&)> doIt) {
        if (!this->head) {
            return;
        }

        typename List<T>::NodePtr start = this->head;
        for (int i = 0; i < startIndex && start; ++i) {
            start = start->next;
        }
        if (!start) {
            start = this->head;
        }

        typename List<T>::NodePtr current = start;
        do {
            doIt(current->data);
            current = current->next;
            if (!current) {
                current = this->head;
            }
        } while (current != start);
    }
};
