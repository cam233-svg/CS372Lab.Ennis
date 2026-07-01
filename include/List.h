#pragma once
#include <functional>
#include <memory>

template <typename T>
class List {
protected:
    class Node {
    public:
        T                     data;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node>   prev;
        Node() = default;
        explicit Node(const T& d) : data(d) {}
    };

    using NodePtr = std::shared_ptr<Node>;

    NodePtr head;
    NodePtr tail;

    void deleteListContents() {
        while (head) {
            NodePtr nxt = head->next;
            head->next.reset();
            head = nxt;
        }
        tail.reset();
    }

    void copyFrom(const List& rhs) {
        for (NodePtr curr = rhs.head; curr; curr = curr->next) {
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

    List(List&& rhs) noexcept
        : head(std::move(rhs.head)), tail(std::move(rhs.tail)) {}

    List& operator=(List&& rhs) noexcept {
        if (this != &rhs) {
            deleteListContents();
            head = std::move(rhs.head);
            tail = std::move(rhs.tail);
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
        NodePtr newNode = std::make_shared<Node>(data);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back(T data) {
        NodePtr newNode = std::make_shared<Node>(data);
        if (!tail) {
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
        if (!head) return;
        head = head->next;
        if (!head) {
            tail.reset();
        } else {
            head->prev.reset();
        }
    }

    void pop_back() {
        if (!tail) return;
        NodePtr prev = tail->prev.lock();
        if (!prev) {
            head.reset();
            tail.reset();
        } else {
            prev->next.reset();
            tail = prev;
        }
    }

    void traverse(std::function<void(T&)> doIt) {
        for (NodePtr current = head; current; current = current->next) {
            doIt(current->data);
        }
    }
};
