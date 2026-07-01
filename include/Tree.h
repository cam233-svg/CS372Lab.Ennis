#pragma once

#include <memory>
#include <functional>
#include <cassert>
#include <initializer_list>
#include <ostream>
#include <queue>

template<typename T>
class Tree
{
    struct Node
    {
        Node(std::shared_ptr<const Node> lft, T val, std::shared_ptr<const Node> rgt)
            : _lft(lft), _val(val), _rgt(rgt)
        {}

        std::shared_ptr<const Node>         _lft;
        T                                   _val;
        std::shared_ptr<const Node>         _rgt;
        mutable std::weak_ptr<const Node>   _parent;
    };

    explicit Tree(std::shared_ptr<const Node> node)
        : _root(node) {}

public:
    Tree() : _root(nullptr) {}
    Tree(Tree const & other) = default;
    Tree & operator=(Tree const & other) = default;
    ~Tree() = default;
    Tree(Tree && other) = default;
    Tree & operator=(Tree && other) = default;

    Tree(Tree lft, T val, Tree rgt)
        : _root(std::make_shared<Node>(lft._root, val, rgt._root))
    {
        if (_root->_lft) _root->_lft->_parent = _root;
        if (_root->_rgt) _root->_rgt->_parent = _root;
    }

    Tree(std::initializer_list<T> init) {
        Tree t;
        for (T v : init) {
            t = t.insert(v);
        }
        _root = t._root;
    }

    bool isEmpty() const { return !_root; }

    size_t size() const {
        if (isEmpty()) return 0;
        return 1 + left().size() + right().size();
    }

    T root() const {
        assert(!isEmpty());
        return _root->_val;
    }

    Tree left() const {
        assert(!isEmpty());
        return Tree(_root->_lft);
    }

    Tree right() const {
        assert(!isEmpty());
        return Tree(_root->_rgt);
    }

    Tree parent() const {
        if (isEmpty()) return Tree();
        return Tree(_root->_parent.lock());
    }

    template <typename Compare = std::greater<T>>
    Tree insert(const T& x, Compare comp = std::greater<T>()) const {
        if (isEmpty())
            return Tree(Tree(), x, Tree());
        T y = root();
        if (comp(x, y))
            return Tree(left().insert(x, comp), y, right());
        else if (comp(y, x))
            return Tree(left(), y, right().insert(x, comp));
        else
            return *this;
    }

    template <typename Compare = std::greater<T>>
    bool member(const T& x, Compare comp = std::greater<T>()) const {
        if (isEmpty()) return false;
        T y = root();
        if (comp(x, y))      return left().member(x, comp);
        else if (comp(y, x)) return right().member(x, comp);
        else                 return true;
    }

    template<typename Compare = std::greater<T>>
    bool find(const T& x, Tree& subtreeWhereFound, Compare comp = std::greater<T>()) const {
        if (isEmpty()) {
            subtreeWhereFound = Tree();
            return false;
        }
        T y = root();
        if (comp(x, y))
            return left().find(x, subtreeWhereFound, comp);
        else if (comp(y, x))
            return right().find(x, subtreeWhereFound, comp);
        else {
            subtreeWhereFound = *this;
            return true;
        }
    }

    void preorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        visit(root());
        left().preorder(visit);
        right().preorder(visit);
    }

    void inorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().inorder(visit);
        visit(root());
        right().inorder(visit);
    }

    void postorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().postorder(visit);
        right().postorder(visit);
        visit(root());
    }

private:
    std::shared_ptr<const Node> _root;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree) {
    if (tree.isEmpty()) {
        os << "[]";
        return os;
    }
    os << "[";
    tree.preorder([&os](T val) { os << val << " "; });
    os << "]";
    return os;
}

namespace treealgo_detail {
    template <typename T, typename Visit>
    void levelStep(std::queue<Tree<T>>& pending, Visit visit) {
        if (pending.empty()) return;
        Tree<T> node = pending.front();
        pending.pop();
        if (!node.isEmpty()) {
            visit(node.root());
            pending.push(node.left());
            pending.push(node.right());
        }
        levelStep(pending, visit);
    }
}

template <typename T, typename Visit>
void levelTraversal(const Tree<T>& tree, Visit visit) {
    std::queue<Tree<T>> pending;
    pending.push(tree);
    treealgo_detail::levelStep(pending, visit);
}

template <typename T>
Tree<T> prune(const Tree<T>& tree) {
    if (tree.isEmpty())
        return Tree<T>();
    if (tree.left().isEmpty() && tree.right().isEmpty())
        return Tree<T>();
    return Tree<T>(prune(tree.left()), tree.root(), prune(tree.right()));
}
