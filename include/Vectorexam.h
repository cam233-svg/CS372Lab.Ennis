#pragma once

#include <iostream>

template <typename T>
class Vector {
public:
    Vector() {
        arr = new T[1];
        vCapacity = 1;
        length = 0;
    }

    Vector(const Vector& obj) {
        vCapacity = obj.vCapacity;
        length = obj.length;
        arr = new T[vCapacity];
        for (int i = 0; i < length; i++) {
            arr[i] = obj.arr[i];
        }
    }

    virtual ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    Vector& operator=(const Vector& source) {
        if (this == &source) return *this;
        delete[] arr;
        arr = new T[source.vCapacity];
        vCapacity = source.vCapacity;
        length = source.length;
        for (int i = 0; i < length; i++) {
            arr[i] = source.arr[i];
        }
        return *this;
    }

    void put(T data, int index) {
        if (index == length) {
            push_back(data);
        } else if (index >= 0 && index < length) {
            arr[index] = data;
        } else {
            std::cerr << "Vector::put: index out of bounds\n";
        }
    }

    void push_back(T data) {
        if (length == vCapacity) {
            expand(nextCapacity());
        }
        arr[length] = data;
        length++;
    }

    T& at(int index) {
        if (index < 0 || index >= length) {
            std::cerr << "Vector: index out of bounds on access" << std::endl;
            exit(1);
        }
        return arr[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= length) {
            std::cerr << "Vector: index out of bounds on access" << std::endl;
            exit(1);
        }
        return arr[index];
    }

    int size() const { return length; }

    virtual int capacity() const { return vCapacity; }

    void traverse() const {
        for (int i = 0; i < length; i++) {
            std::cout << arr[i] << std::endl;
        }
        std::cout << std::endl;
    }

    bool operator==(Vector& other) const {
        if (other.size() != length) return false;
        for (int i = 0; i < length; i++) {
            if (arr[i] != other.at(i)) return false;
        }
        return true;
    }

    T& operator[](int i) {
        if ((i < 0) || (i >= length)) {
            std::cerr << std::endl << "Vector index out of bounds" << std::endl;
            exit(1);
        }
        return at(i);
    }

    const T& operator[](int i) const {
        if ((i < 0) || (i >= length)) {
            std::cerr << std::endl << "Vector index out of bounds" << std::endl;
            exit(1);
        }
        return arr[i];
    }

    class Iterator {
    public:
        Iterator(Vector<T>* vec, int index) : vec(vec), index(index) {}

        T& operator*() {
            return vec->arr[index];
        }

        Iterator& operator++() {
            index++;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return vec == other.vec && index == other.index;
        }

    private:
        Vector<T>* vec;
        int index;
    };

    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, length);
    }

protected:
    T* arr;
    int vCapacity;
    int length;

    virtual int nextCapacity() const {
        return 2 * vCapacity;
    }

    virtual void expand(int newCapacity) {
        if (newCapacity > vCapacity) {
            T* temp = new T[newCapacity];
            for (int i = 0; i < length; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            vCapacity = newCapacity;
            arr = temp;
        } else {
            std::cerr << "vector::expand: new capacity is less than equal to current\n";
        }
    }
};
