#pragma once
#include "List.h"
#include <functional>

template <typename T>
class CircularList : public List<T> {
public:
    using List<T>::traverse;

    void traverse(int startIndex, std::function<void(T&)> doIt) {
        if (this->head == nullptr) {
            return;
        }

        typename List<T>::Node* start = this->head;
        for (int i = 0; i < startIndex && start != nullptr; ++i) {
            start = start->next;
        }
        if (start == nullptr) {
            start = this->head;
        }

        typename List<T>::Node* current = start;
        do {
            doIt(current->data);
            current = current->next;
            if (current == nullptr) {
                current = this->head;
            }
        } while (current != start);
    }
};
