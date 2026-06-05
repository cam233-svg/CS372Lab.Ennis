#pragma once

#include <algorithm>
#include "Vector.h"

template <typename T>
class VectorSTLCopy : public Vector<T> {
public:
    VectorSTLCopy() : Vector<T>() {}

protected:
    void expand(int newCapacity) override {
        if (newCapacity > this->vCapacity) {
            T* temp = new T[newCapacity];
            std::copy(this->arr, this->arr + this->length, temp);
            delete[] this->arr;
            this->vCapacity = newCapacity;
            this->arr = temp;
        } else {
            std::cerr << "VectorSTLCopy::expand: new capacity is less than equal to current\n";
        }
    }
};