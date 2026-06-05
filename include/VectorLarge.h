#pragma once

#include "Vector.h"

template <typename T>
class VectorLarge : public Vector<T> {
public:
    VectorLarge() : Vector<T>() {
        delete[] this->arr;
        this->arr = new T[128];
        this->vCapacity = 128;
    }

protected:
    int nextCapacity() const override {
        return 4 * this->vCapacity;
    }

};