#pragma once
#include "Tree.hpp"
#include "Pair.h"
#include "List.h"
#include <stdexcept>

template <typename Key, typename Value>
class Dictionary {
private:
    using Entry = Pair<Key, Value>;

    struct KeyOrder {
        bool operator()(const Entry& a, const Entry& b) const {
            return a.first < b.first;
        }
    };

    Tree<Entry> tree;
    List<Key>   keyCache;
    List<Value> valueCache;

    static Entry probe(const Key& key) {
        return Entry{ key, Value{} };
    }

    void setValue(const Key& key, const Value& value) {
        Tree<Entry> rebuilt;
        bool replaced = false;
        tree.inorder([&](Entry e) {
            if (e.first == key) {
                e.second = value;
                replaced = true;
            }
            rebuilt = rebuilt.insert(e, KeyOrder{});
        });
        if (!replaced) {
            rebuilt = rebuilt.insert(Entry{ key, value }, KeyOrder{});
        }
        tree = rebuilt;
    }

public:
    Dictionary() = default;

    Dictionary(const Dictionary& other)
        : tree(other.tree), keyCache(other.keyCache), valueCache(other.valueCache) {}

    Dictionary& operator=(const Dictionary& other) {
        if (this != &other) {
            tree       = other.tree;
            keyCache   = other.keyCache;
            valueCache = other.valueCache;
        }
        return *this;
    }

    Dictionary(Dictionary&& other) noexcept
        : tree(std::move(other.tree))
        , keyCache(std::move(other.keyCache))
        , valueCache(std::move(other.valueCache)) {}

    Dictionary& operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            tree       = std::move(other.tree);
            keyCache   = std::move(other.keyCache);
            valueCache = std::move(other.valueCache);
        }
        return *this;
    }

    ~Dictionary() = default;

    bool isEmpty() const { return tree.isEmpty(); }
    int  size()    const { return static_cast<int>(tree.size()); }

    bool contains(const Key& key) const {
        return tree.member(probe(key), KeyOrder{});
    }

    class Reference {
        Dictionary& dict;
        Key         key;
    public:
        Reference(Dictionary& d, const Key& k) : dict(d), key(k) {}

        operator Value() const { return dict.at(key); }

        Reference& operator=(const Value& value) {
            dict.setValue(key, value);
            return *this;
        }
        Reference& operator=(const Reference& other) {
            return (*this = static_cast<Value>(other));
        }
    };

    Reference operator[](const Key& key) {
        if (!contains(key)) {
            setValue(key, Value{});
        }
        return Reference(*this, key);
    }

    Value at(const Key& key) const {
        Tree<Entry> found;
        if (tree.find(probe(key), found, KeyOrder{})) {
            return found.root().second;
        }
        throw std::out_of_range("Dictionary::at: key not found");
    }

    void insert(const Key& key, const Value& value) { setValue(key, value); }
    void insert(const Entry& entry) { setValue(entry.first, entry.second); }

    void erase(const Key& key) {
        Tree<Entry> rebuilt;
        tree.inorder([&](Entry e) {
            if (!(e.first == key)) {
                rebuilt = rebuilt.insert(e, KeyOrder{});
            }
        });
        tree = rebuilt;
    }

    void clear() { tree = Tree<Entry>{}; }

    List<Key>& keys() {
        keyCache = List<Key>{};
        tree.inorder([&](Entry e) { keyCache.push_back(e.first); });
        return keyCache;
    }

    List<Value>& values() {
        valueCache = List<Value>{};
        tree.inorder([&](Entry e) { valueCache.push_back(e.second); });
        return valueCache;
    }
};
