#pragma once

#include <queue>
#include <stdexcept>

#include "Tree.hpp"

namespace algorithms {

/**
 * Ordinary binary search tree implementation.
 */
template<typename Key, typename Value, typename Compare = std::less<Key>>
class BinarySearchTree : public Tree<Key, Value, Compare> {
public:
    using KeyType = typename Tree<Key, Value, Compare>::KeyType;
    using ValueType = typename Tree<Key, Value, Compare>::ValueType;
    using KeyTypeOrNull = typename Tree<Key, Value, Compare>::KeyTypeOrNull;
    using ValueTypeOrNull = typename Tree<Key, Value, Compare>::ValueTypeOrNull;
    using KeysType = typename Tree<Key, Value, Compare>::KeysType;
    using Callback = typename Tree<Key, Value, Compare>::Callback;
    using TraverseOrder = typename Tree<Key, Value, Compare>::TraverseOrder;

public:
    BinarySearchTree()
        : _root{nullptr}
    {
    }

    ~BinarySearchTree()
    {
        clear();
    }

    void put(const KeyType& key, const ValueType& value) override
    {
        _root = put(_root, key, value);
    }

    ValueType& get(const KeyType& key) override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = find(key);
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
        return n->value;
    }

    const ValueType& get(const KeyType& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = find(key);
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
        return n->value;
    }

    ValueTypeOrNull pick(const KeyType& key) const override
    {
        auto n = find(key);
        return n ? ValueTypeOrNull{n->value} : std::nullopt;
    }

    bool contains(const KeyType& key) const override
    {
        return (find(key) != nullptr);
    }

    void erase(const KeyType& key) override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        _root = erase(_root, key);
    }

    void eraseMin() override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        _root = eraseMin(_root);
    }

    void eraseMax() override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        _root = eraseMax(_root);
    }

    void clear() override
    {
        clear(_root);
    }

    bool empty() const override
    {
        return !_root;
    }

    std::size_t size() const override
    {
        return size(_root);
    }

    std::size_t size(KeyType lo, KeyType hi) const override
    {
        if (contains(hi)) {
            return rank(hi) - rank(lo) + 1;
        }
        return rank(hi) - rank(lo);
    }

    std::size_t rank(const KeyType& key) const override
    {
        return rank(key, _root);
    }

    KeyType min() const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        return min(_root)->key;
    }

    KeyType max() const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        return max(_root)->key;
    }

    KeyTypeOrNull floor(const KeyType& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = floor(_root, key);
        return n ? KeyTypeOrNull{n->key} : std::nullopt;
    }

    KeyTypeOrNull ceiling(const KeyType& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = ceiling(_root, key);
        return n ? KeyTypeOrNull{n->key} : std::nullopt;
    }

    KeysType keys() const override
    {
        return keys(min(), max());
    }

    KeysType keys(Key lo, Key hi) const override
    {
        if (empty() || compare(lo, hi) > 0) {
            return KeysType{};
        }

        KeysType output;
        keys(_root, output, lo, hi);
        return output;
    }

    void traverse(TraverseOrder type, Callback callback) override
    {
        if (!callback) {
            throw std::runtime_error{"Invalid callback object"};
        }

        switch (type) {
        case TraverseOrder::DepthPreOrder:
            depthPreOrder(_root, callback);
            break;
        case TraverseOrder::DepthInOrder:
            depthInOrder(_root, callback);
            break;
        case TraverseOrder::DepthPostOrder:
            depthPostOrder(_root, callback);
            break;
        case TraverseOrder::Breadth:
            breadthOrder(_root, callback);
            break;
        }
    }

private:
    struct Node {
        Node(KeyType key, ValueType value)
            : key{key}
            , value{value}
            , lh{nullptr}
            , rh{nullptr}
            , count{1}
        {
        }

        KeyType key;
        ValueType value;
        Node* lh;
        Node* rh;
        std::size_t count;
    };

private:
    std::size_t size(Node* node) const
    {
        if (!node) {
            return 0;
        }
        return node->count;
    }

    int compare(const KeyType& k1, const KeyType& k2) const
    {
        if (_compare(k1, k2)) {
            return -1;
        }
        if (_compare(k2, k1)) {
            return +1;
        }
        return 0;
    }

    Node* find(const KeyType& key) const
    {
        Node* n = _root;
        while (n) {
            auto c = compare(key, n->key);
            if (c == 0) {
                return n;
            }
            else if (c < 0) {
                n = n->lh;
            }
            else if (c > 0) {
                n = n->rh;
            }
        }
        return nullptr;
    }

    Node* put(Node* node, const KeyType& key, const ValueType& value)
    {
        if (!node) {
            return new Node{key, value};
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            node->value = value;
        }
        else if (c < 0) {
            node->lh = put(node->lh, key, value);
        }
        else if (c > 0) {
            node->rh = put(node->rh, key, value);
        }
        node->count = 1 + size(node->lh) + size(node->rh);

        return node;
    }

    Node* floor(Node* node, const KeyType& key) const
    {
        if (!node) {
            return nullptr;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            return node;
        }
        if (c < 0) {
            return floor(node->lh, key);
        }
        if (c > 0) {
            Node* t = floor(node->rh, key);
            return t ? t : node;
        }

        return nullptr;
    }

    Node* ceiling(Node* node, const KeyType& key) const
    {
        if (!node) {
            return nullptr;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            return node;
        }
        if (c < 0) {
            Node* t = ceiling(node->lh, key);
            return t ? t : node;
        }
        if (c > 0) {
            return ceiling(node->rh, key);
        }

        return nullptr;
    }

    std::size_t rank(const KeyType& key, Node* node) const
    {
        if (!node) {
            return 0;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            return size(node->lh);
        }
        if (c < 0) {
            return rank(key, node->lh);
        }
        if (c > 0) {
            return 1 + size(node->lh) + rank(key, node->rh);
        }

        return 0;
    }

    Node* erase(Node* node, const KeyType& key)
    {
        if (!node) {
            return nullptr;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            if (!node->rh) {
                Node* t = node->lh;
                delete node;
                return t ? t->lh : nullptr;
            }

            Node* t = node;
            node = min(t->rh);
            node->rh = dropMin(t->rh);
            node->lh = t->lh;
            delete t;
        }
        else if (c < 0) {
            node->lh = erase(node->lh, key);
        }
        else if (c > 0) {
            node->rh = erase(node->rh, key);
        }
        node->count = 1 + size(node->lh) + size(node->rh);

        return node;
    }

    Node* eraseMin(Node* node)
    {
        if (!node->lh) {
            Node* t = node->rh;
            delete node;
            return t;
        }
        node->lh = eraseMin(node->lh);
        node->count = 1 + size(node->lh) + size(node->rh);
        return node;
    }

    Node* eraseMax(Node* node)
    {
        if (!node->rh) {
            Node* t = node->lh;
            delete node;
            return t;
        }
        node->rh = eraseMax(node->rh);
        node->count = 1 + size(node->lh) + size(node->rh);
        return node;
    }

    Node* min(Node* node) const
    {
        return node->lh ? min(node->lh) : node;
    }

    Node* max(Node* node) const
    {
        return node->rh ? max(node->rh) : node;
    }

    void keys(Node* node, KeysType& output, const KeyType& lo, const KeyType& hi) const
    {
        if (!node) {
            return;
        }

        auto loc = compare(lo, node->key);
        auto hic = compare(hi, node->key);

        if (loc < 0) {
            keys(node->lh, output, lo, hi);
        }
        if (loc <= 0 && hic >= 0) {
            output.push_back(node->key);
        }
        if (hic > 0) {
            keys(node->rh, output, lo, hi);
        }
    }

    Node* dropMin(Node* node)
    {
        if (!node->lh) {
            return node->rh;
        }
        node->lh = dropMin(node->lh);
        node->count = 1 + size(node->lh) + size(node->rh);
        return node;
    }

    void depthPreOrder(Node* node, const Callback& callback)
    {
        if (!node) {
            return;
        }

        callback(node->key, node->value);
        depthPreOrder(node->lh, callback);
        depthPreOrder(node->rh, callback);
    }

    void depthInOrder(Node* node, const Callback& callback)
    {
        if (!node) {
            return;
        }

        depthPreOrder(node->lh, callback);
        callback(node->key, node->value);
        depthPreOrder(node->rh, callback);
    }

    void depthPostOrder(Node* node, const Callback& callback)
    {
        if (!node) {
            return;
        }

        depthPreOrder(node->lh, callback);
        depthPreOrder(node->rh, callback);
        callback(node->key, node->value);
    }

    void breadthOrder(Node* node, const Callback& callback)
    {
        if (!node) {
            return;
        }

        std::queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            auto e = q.front();
            callback(e->key, e->value);
            if (e->lh) {
                q.push(e->lh);
            }
            if (e->rh) {
                q.push(e->rh);
            }
            q.pop();
        }
    }

    void clear(Node* node)
    {
        if (!node) {
            return;
        }

        clear(node->lh);
        clear(node->rh);
        delete node;
    }

private:
    Node* _root;
    Compare _compare;
};

} // namespace algorithms
