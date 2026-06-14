#pragma once
#include <functional>

template <typename T>
class List {
protected:
    class Node {
    public:
        T     data;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node() = default;
        explicit Node(const T& d) : data(d) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    void deleteListContents() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current->next;
            delete current;
            current = temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    void copyFrom(const List& rhs) {
        for (Node* curr = rhs.head; curr != nullptr; curr = curr->next) {
            push_back(curr->data);
        }
    }

public:
    List() = default;

    List(T newData) {
        push_back(newData);
    }

    List(const List& rhs) {
        copyFrom(rhs);
    }

    List& operator=(const List& rhs) {
        if (this != &rhs) {
            deleteListContents();
            copyFrom(rhs);
        }
        return *this;
    }

    List(List&& rhs) {
        head = rhs.head;
        tail = rhs.tail;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    List& operator=(List&& rhs) {
        if (this != &rhs) {
            deleteListContents();
            head = rhs.head;
            tail = rhs.tail;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }
        return *this;
    }

    ~List() {
        deleteListContents();
    }

    bool empty() const {
        return head == nullptr;
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back(T data) {
        Node* newNode = new Node(data);
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    T& front() {
        return head->data;
    }

    const T& front() const {
        return head->data;
    }

    T& back() {
        return tail->data;
    }

    const T& back() const {
        return tail->data;
    }

    void pop_front() {
        if (head == nullptr) return;
        Node* firstNode = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }
        delete firstNode;
    }

    void pop_back() {
        if (tail == nullptr) return;
        Node* lastNode = tail;
        tail = tail->prev;
        if (tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }
        delete lastNode;
    }

    void traverse(std::function<void(T&)> doIt) {
        Node* current = head;
        while (current != nullptr) {
            doIt(current->data);
            current = current->next;
        }
    }
};
