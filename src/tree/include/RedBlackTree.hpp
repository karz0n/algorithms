#pragma once

#include "Traverse.hpp"

#include <stdexcept>
#include <vector>
#include <optional>

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
class RedBlackTree {
public:
    using KeyOrNullType = std::optional<Key>;
    using ValueOrNullType = std::optional<Value>;
    using KeysType = std::vector<Key>;
    using CallbackType = std::function<void(const Key&, Value&)>;

public:
    RedBlackTree()
        : _root{nullptr}
    {
    }

    ~RedBlackTree()
    {
        clear();
    }

    /**
     * Puts element with given key and value.
     *
     * @param key The key of element
     * @param value The value of element
     */
    void
    put(const Key& key, const Value& value)
    {
        _root = put(_root, key, value);

        /** Root is always black */
        _root->color = Node::Colors::black;
    }

    /**
     * Get element with given key.
     *
     * @param key The target key
     *
     * @return The reference to element
     */
    Value&
    get(const Key& key)
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

    /**
     * Get element with given key.
     *
     * @param key The target key
     *
     * @return The reference to element
     */
    const Value&
    get(const Key& key) const
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

    /**
     * Picks element with given key.
     *
     * @param key The target key
     *
     * @return The element or null
     */
    ValueOrNullType
    pick(const Key& key) const
    {
        auto n = find(key);
        return n ? ValueOrNullType{n->value} : std::nullopt;
    }

    /**
     * Checks if tree contains element with given key
     *
     * @param key The target key.
     *
     * @return \c true if contained, \c false otherwise
     */
    bool
    contains(const Key& key) const
    {
        return (find(key) != nullptr);
    }

    /**
     * Erase element by given key.
     *
     * @param key The key of element to erase
     */
    void
    erase(const Key& key)
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

    /**
     * Erase min element.
     */
    void
    eraseMin()
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

    /**
     * Erase max element.
     */
    void
    eraseMax()
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

    /**
     * Erase all elements.
     */
    void
    clear()
    {
        clear(_root);
    }

    /**
     * Checks for empty.
     *
     * @return \c true If empty, \c false otherwise
     */
    bool
    empty() const
    {
        return !_root;
    }

    /**
     * Returns the total number of elements.
     *
     * @return The number of elements
     */
    std::size_t
    size() const
    {
        return size(_root);
    }

    /**
     * Returns the number of elements in the range [lo, hi].
     *
     * @param lo The left bound
     * @param hi The right bound
     *
     * @return The number of element
     */
    std::size_t
    size(Key lo, Key hi) const
    {
        return contains(hi) ? rank(hi) - rank(lo) + 1 : rank(hi) - rank(lo);
    }

    /**
     * Returns the order number of element with given number.
     *
     * @param key The key of element
     *
     * @return The order number of element
     */
    std::size_t
    rank(const Key& key) const
    {
        return rank(key, _root);
    }

    /**
     * Returns the key of min element.
     *
     * @return The key of element
     */
    Key
    min() const
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        return min(_root)->key;
    }

    /**
     * Returns the key of max element.
     *
     * @return The key of element
     */
    Key
    max() const
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        return max(_root)->key;
    }

    /**
     * Returns the last not greater or equal of given key.
     *
     * @param key The target key
     *
     * @return The key value or null
     */
    KeyOrNullType
    floor(const Key& key) const
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = floor(_root, key);
        return n ? KeyOrNullType{n->key} : std::nullopt;
    }

    /**
     * Returns the firts greater than given key.
     *
     * @param key The target key.
     *
     * @return
     */
    KeyOrNullType
    ceiling(const Key& key) const
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = ceiling(_root, key);
        return n ? KeyOrNullType{n->key} : std::nullopt;
    }

    /**
     * Returns the list of contained keys.
     *
     * @return The list of contained keys
     */
    KeysType
    keys() const
    {
        return keys(min(), max());
    }

    /**
     * Returns the keys in the range [lo, hi].
     *
     * @param lo The left bound
     * @param hi The right bound
     *
     * @return The list of keys
     */
    KeysType
    keys(Key lo, Key hi) const
    {
        if (empty() || compare(lo, hi) > 0) {
            return {};
        }

        KeysType output;
        keys(_root, output, lo, hi);
        return output;
    }

    /**
     * Traverses tree.
     *
     * @param order The order of traversing
     * @param callback The method that will be called for each node
     */
    void
    traverse(TraverseOrder order, CallbackType callback, bool recursion = true)
    {
        if (order == TraverseOrder::DepthPreOrder) {
            recursion
                ? DepthPreOrderTraverser<Node>{_root}.traverse(std::move(callback))
                : DepthPreOrderNoRecTraverser<Node>{_root}.traverse(std::move(callback));
            return;
        }
        if (order == TraverseOrder::DepthInOrder) {
            recursion
                ? DepthInOrderTraverser<Node>{_root}.traverse(std::move(callback))
                : DepthInOrderNoRecTraverser<Node>{_root}.traverse(std::move(callback));
            return;
        }
        if (order == TraverseOrder::DepthPostOrder) {
            recursion
                ? DepthPostOrderTraverser<Node>{_root}.traverse(std::move(callback))
                : DepthPostOrderNoRecTraverser<Node>{_root}.traverse(std::move(callback));
            return;
        }
        if (order == TraverseOrder::BreadthOrder) {
            BreadthOrderTraverser<Node>{_root}.traverse(std::move(callback));
            return;
        }
        throw std::logic_error{"Unknown traverse order"};
    }

private:
    struct Node {
        enum class Colors { red = true,
                            black = false };

        using KeyType = Key;
        using ValueType = Value;

        Node(const Key& key, const Value& value)
            : key{key}
            , value{value}
            , lh{nullptr}
            , rh{nullptr}
            , count{1}
            , color{Colors::red} /** New nodes are always red */
        {
        }

        Key key;
        Value value;
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
    compare(const Key& k1, const Key& k2) const
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
    put(Node* node, const Key& key, const Value& value)
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
    floor(Node* node, const Key& key) const
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
    ceiling(Node* node, const Key& key) const
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
    rank(const Key& key, Node* node) const
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
    erase(Node* node, const Key& key)
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
    find(const Key& key) const
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
    keys(Node* n, KeysType& output, const Key& lo, const Key& hi) const
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
