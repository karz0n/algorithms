#pragma once

#include <queue>
#include <stdexcept>

#include "Tree.hpp"

/**
 * Red-black tree implementation (LLRB).
 *
 * Rules:
 *  - Every node is red or black
 *  - Root is always black
 *  - New nodes are always red
 *  - Every path from root to null link has the same number of black links (perfect black balance)
 *  - No path can have two consecutive red nodes
 *  - Nulls are black
 *  - Red link lean left
 */
namespace algorithms {

template<typename Key, typename Value, typename Compare = std::less<Key>>
class RedBlackTree : public Tree<Key, Value, Compare> {
public:
    using KeyType = typename Tree<Key, Value, Compare>::KeyType;
    using ValueType = typename Tree<Key, Value, Compare>::ValueType;
    using KeyTypeOrNull = typename Tree<Key, Value, Compare>::KeyTypeOrNull;
    using ValueTypeOrNull = typename Tree<Key, Value, Compare>::ValueTypeOrNull;
    using KeysType = typename Tree<Key, Value, Compare>::KeysType;
    using Callback = typename Tree<Key, Value, Compare>::Callback;
    using TraverseOrder = typename Tree<Key, Value, Compare>::TraverseOrder;

public:
    RedBlackTree()
        : _root{nullptr}
    {
    }

    ~RedBlackTree()
    {
        clear();
    }

    void
    put(const KeyType& key, const ValueType& value) override
    {
        _root = put(_root, key, value);

        /** Root is always black */
        _root->color = Node::Colors::black;
    }

    ValueType&
    get(const KeyType& key) override
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

    const ValueType&
    get(const KeyType& key) const override
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

    ValueTypeOrNull
    pick(const KeyType& key) const override
    {
        auto n = find(key);
        return n ? ValueTypeOrNull{n->value} : std::nullopt;
    }

    bool
    contains(const KeyType& key) const override
    {
        return (find(key) != nullptr);
    }

    void
    erase(const KeyType& key) override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        if (!contains(key)) {
            return;
        }

        if (!isRed(_root->lh) && !isRed(_root->rh)) {
            _root->color = Node::Colors::red;
        }
        _root = erase(_root, key);
        if (!empty()) {
            _root->color = Node::Colors::black;
        }
    }

    void
    eraseMin() override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }

        if (!isRed(_root->lh) && !isRed(_root->rh)) {
            _root->color = Node::Colors::red;
        }
        _root = eraseMin(_root);
        if (!empty()) {
            _root->color = Node::Colors::black;
        }
    }

    void
    eraseMax() override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }

        if (!isRed(_root->lh) && !isRed(_root->rh)) {
            _root->color = Node::Colors::red;
        }
        _root = eraseMax(_root);
        if (!empty()) {
            _root->color = Node::Colors::black;
        }
    }

    void
    clear() override
    {
        clear(_root);
    }

    bool
    empty() const override
    {
        return !_root;
    }

    std::size_t
    size() const override
    {
        return size(_root);
    }

    std::size_t
    size(KeyType lo, KeyType hi) const override
    {
        return contains(hi) ? rank(hi) - rank(lo) + 1 : rank(hi) - rank(lo);
    }

    std::size_t
    rank(const KeyType& key) const override
    {
        return rank(key, _root);
    }

    KeyType
    min() const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        return min(_root)->key;
    }

    KeyType
    max() const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        return max(_root)->key;
    }

    KeyTypeOrNull
    floor(const KeyType& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = floor(_root, key);
        return n ? KeyTypeOrNull{n->key} : std::nullopt;
    }

    KeyTypeOrNull
    ceiling(const KeyType& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = ceiling(_root, key);
        return n ? KeyTypeOrNull{n->key} : std::nullopt;
    }

    KeysType
    keys() const override
    {
        return keys(min(), max());
    }

    KeysType
    keys(KeyType lo, KeyType hi) const override
    {
        if (empty() || compare(lo, hi) > 0) {
            return {};
        }

        KeysType output;
        keys(_root, output, lo, hi);
        return output;
    }

    void
    traverse(TraverseOrder type, Callback callback) override
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
        enum class Colors { red = true,
                            black = false };

        Node(const KeyType& key, const ValueType& value)
            : key{key}
            , value{value}
            , lh{nullptr}
            , rh{nullptr}
            , count{1}
            , color{Colors::red} /** New nodes are always red */
        {
        }

        KeyType key;
        ValueType value;
        Node* lh;
        Node* rh;
        std::size_t count;
        Colors color;
    };

private:
    std::size_t
    size(Node* node) const
    {
        if (!node) {
            return 0;
        }
        return node->count;
    }

    int
    compare(const KeyType& k1, const KeyType& k2) const
    {
        if (_compare(k1, k2)) {
            return -1;
        }
        if (_compare(k2, k1)) {
            return +1;
        }
        return 0;
    }

    Node*
    put(Node* node, const KeyType& key, const ValueType& value)
    {
        if (!node) {
            return new Node{key, value};
        }

        /** Put node as usual */
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

        /** Balance 2-3 node (red-black tree) */
        if (isRed(node->rh) && !isRed(node->lh)) {
            node = rotateLeft(node);
        }
        if (isRed(node->lh) && isRed(node->lh->lh)) {
            node = rotateRight(node);
        }
        if (isRed(node->lh) && isRed(node->rh)) {
            flipColors(node);
        }

        node->count = 1 + size(node->lh) + size(node->rh);

        return node;
    }

    Node*
    floor(Node* node, const KeyType& key) const
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

    Node*
    ceiling(Node* node, const KeyType& key) const
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

    std::size_t
    rank(const KeyType& key, Node* node) const
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

    Node*
    erase(Node* node, const KeyType& key)
    {
        auto c = compare(key, node->key);
        if (c < 0) {
            if (!isRed(node->lh) && !isRed(node->lh->lh)) {
                node = moveRedLeft(node);
            }
            node->lh = erase(node->lh, key);
        }
        else {
            if (isRed(node->lh)) {
                node = rotateRight(node);
            }
            if (compare(key, node->key) == 0 && !node->rh) {
                delete node;
                return nullptr;
            }
            if (!isRed(node->rh) && !isRed(node->rh->lh)) {
                node = moveRedRight(node);
            }
            if (compare(key, node->key) == 0) {
                auto t = min(node->rh);
                node->key = t->key;
                node->value = t->value;
                node->rh = dropMin(node->rh);
                delete t;
            }
            else {
                node->rh = erase(node->rh, key);
            }
        }
        return balance(node);
    }

    Node*
    eraseMin(Node* node)
    {
        if (!node->lh) {
            delete node;
            return nullptr;
        }
        if (!isRed(node->lh) && !isRed(node->lh->lh)) {
            node = moveRedLeft(node);
        }
        node->lh = eraseMin(node->lh);
        return balance(node);
    }

    Node*
    eraseMax(Node* node)
    {
        if (isRed(node->lh)) {
            node = rotateRight(node);
        }
        if (!node->rh) {
            delete node;
            return nullptr;
        }
        if (!isRed(node->rh) && !isRed(node->rh->rh)) {
            node = moveRedRight(node);
        }
        node->rh = eraseMax(node->rh);
        return balance(node);
    }

    Node*
    dropMin(Node* node)
    {
        if (!node->lh) {
            return nullptr;
        }
        if (!isRed(node->lh) && !isRed(node->lh->lh)) {
            node = moveRedLeft(node);
        }
        node->lh = dropMin(node->lh);
        return balance(node);
    }

    Node*
    find(const KeyType& key) const
    {
        Node* node = _root;
        while (node) {
            auto c = compare(key, node->key);
            if (c == 0) {
                return node;
            }
            else if (c < 0) {
                node = node->lh;
            }
            else if (c > 0) {
                node = node->rh;
            }
        }
        return nullptr;
    }

    Node*
    min(Node* node) const
    {
        return (node->lh) ? min(node->lh) : node;
    }

    Node*
    max(Node* node) const
    {
        return (node->rh) ? max(node->rh) : node;
    }

    void
    keys(Node* n, KeysType& output, const KeyType& lo, const KeyType& hi) const
    {
        if (!n) {
            return;
        }

        auto loc = compare(lo, n->key);
        auto hic = compare(hi, n->key);

        if (loc < 0) {
            keys(n->lh, output, lo, hi);
        }
        if (loc <= 0 && hic >= 0) {
            output.push_back(n->key);
        }
        if (hic > 0) {
            keys(n->rh, output, lo, hi);
        }
    }

    Node*
    rotateLeft(Node* node)
    {
        Node* x = node->rh;
        node->rh = x->lh;
        x->lh = node;
        x->color = node->color;
        node->color = Node::Colors::red;
        x->count = node->count;
        node->count = size(node->lh) + size(node->rh) + 1;
        return x;
    }

    Node*
    rotateRight(Node* node)
    {
        Node* x = node->lh;
        node->lh = x->rh;
        x->rh = node;
        x->color = node->color;
        node->color = Node::Colors::red;
        x->count = node->count;
        node->count = size(node->lh) + size(node->rh) + 1;
        return x;
    }

    void
    flipColors(Node* node)
    {
        node->color = invert(node->color);
        node->lh->color = invert(node->lh->color);
        node->rh->color = invert(node->rh->color);
    }

    Node*
    balance(Node* node)
    {
        if (isRed(node->rh)) {
            node = rotateLeft(node);
        }
        if (isRed(node->lh) && isRed(node->lh->lh)) {
            node = rotateRight(node);
        }
        if (isRed(node->lh) && isRed(node->rh)) {
            flipColors(node);
        }
        node->count = size(node->lh) + size(node->rh) + 1;
        return node;
    }

    Node*
    moveRedLeft(Node* node)
    {
        flipColors(node);
        if (isRed(node->rh->lh)) {
            node->rh = rotateRight(node->rh);
            node = rotateLeft(node);
            flipColors(node);
        }
        return node;
    }

    Node*
    moveRedRight(Node* node)
    {
        flipColors(node);
        if (isRed(node->lh->lh)) {
            node = rotateRight(node);
            flipColors(node);
        }
        return node;
    }

    static bool
    isRed(Node* node)
    {
        return node ? (node->color == Node::Colors::red) : false;
    }

    static typename Node::Colors
    invert(typename Node::Colors color)
    {
        return (color == Node::Colors::red) ? Node::Colors::black : Node::Colors::red;
    }

    void
    depthPreOrder(Node* node, const Callback& callback)
    {
        if (!node) {
            return;
        }

        callback(node->key, node->value);
        depthPreOrder(node->lh, callback);
        depthPreOrder(node->rh, callback);
    }

    void
    depthInOrder(Node* node, const Callback& callback)
    {
        if (!node) {
            return;
        }

        depthPreOrder(node->lh, callback);
        callback(node->key, node->value);
        depthPreOrder(node->rh, callback);
    }

    void
    depthPostOrder(Node* node, const Callback& callback)
    {
        if (!node) {
            return;
        }

        depthPreOrder(node->lh, callback);
        depthPreOrder(node->rh, callback);
        callback(node->key, node->value);
    }

    void
    breadthOrder(Node* node, const Callback& callback)
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

    void
    clear(Node* node)
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
