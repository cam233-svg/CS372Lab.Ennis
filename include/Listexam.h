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
        bool  deleted = false;   
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
        deletedCount = 0;
        notDeletedCount = 0;
    }

    void copyFrom(const List& rhs) {
        for (Node* curr = rhs.head; curr != nullptr; curr = curr->next) {
            if (!curr->deleted) {
                push_back(curr->data);
            }
        }
    }

private:
    int deletedCount = 0;       
    int notDeletedCount = 0;    

    
    void purgeDeleted() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            if (current->deleted) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
            }
            current = nextNode;
        }
        deletedCount = 0;
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
        deletedCount = rhs.deletedCount;
        notDeletedCount = rhs.notDeletedCount;
        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.deletedCount = 0;
        rhs.notDeletedCount = 0;
    }

    List& operator=(List&& rhs) {
        if (this != &rhs) {
            deleteListContents();
            head = rhs.head;
            tail = rhs.tail;
            deletedCount = rhs.deletedCount;
            notDeletedCount = rhs.notDeletedCount;
            rhs.head = nullptr;
            rhs.tail = nullptr;
            rhs.deletedCount = 0;
            rhs.notDeletedCount = 0;
        }
        return *this;
    }

    ~List() {
        deleteListContents();
    }

    bool empty() const {
        return notDeletedCount == 0;
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
        notDeletedCount++;
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
        notDeletedCount++;
    }

    T& front() {
        Node* current = head;
        while (current != nullptr && current->deleted) {
            current = current->next;
        }
        return current->data;
    }

    const T& front() const {
        Node* current = head;
        while (current != nullptr && current->deleted) {
            current = current->next;
        }
        return current->data;
    }

    T& back() {
        Node* current = tail;
        while (current != nullptr && current->deleted) {
            current = current->prev;
        }
        return current->data;
    }

    const T& back() const {
        Node* current = tail;
        while (current != nullptr && current->deleted) {
            current = current->prev;
        }
        return current->data;
    }

    void pop_front() {
        Node* current = head;
        while (current != nullptr && current->deleted) {
            current = current->next;
        }
        if (current == nullptr) return;
        current->deleted = true;
        deletedCount++;
        notDeletedCount--;
        if (deletedCount == notDeletedCount) {
            purgeDeleted();
        }
    }

    void pop_back() {
        Node* current = tail;
        while (current != nullptr && current->deleted) {
            current = current->prev;
        }
        if (current == nullptr) return;
        current->deleted = true;
        deletedCount++;
        notDeletedCount--;
        if (deletedCount == notDeletedCount) {
            purgeDeleted();
        }
    }

    void traverse(std::function<void(T&)> doIt) {
        Node* current = head;
        while (current != nullptr) {
            if (!current->deleted) {
                doIt(current->data);
            }
            current = current->next;
        }
    }
};
