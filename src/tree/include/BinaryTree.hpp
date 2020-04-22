#pragma once

#include "Traverse.hpp"

#include <stdexcept>
#include <vector>
#include <optional>

namespace algorithms {

/**
 * Ordinary binary search tree implementation.
 */
template<typename Key, typename Value, typename Compare = std::less<Key>>
class BinaryTree {
public:
    using KeyOrNullType = std::optional<Key>;
    using ValueOrNullType = std::optional<Value>;
    using KeysType = std::vector<Key>;
    using CallbackType = std::function<void(const Key&, Value&)>;

public:
    BinaryTree()
        : _root{nullptr}
    {
    }

    ~BinaryTree()
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
        _root = erase(_root, key);
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
        _root = eraseMin(_root);
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
        _root = eraseMax(_root);
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
            return KeysType{};
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
    traverse(TraverseOrder order, CallbackType callback)
    {
        if (order == TraverseOrder::DepthPreOrder) {
            DepthPreOrderTraverser<Node>{_root}.traverse(std::move(callback));
            return;
        }
        if (order == TraverseOrder::DepthInOrder) {
            DepthInOrderTraverser<Node>{_root}.traverse(std::move(callback));
            return;
        }
        if (order == TraverseOrder::DepthPostOrder) {
            DepthPostOrderTraverser<Node>{_root}.traverse(std::move(callback));
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
        using KeyType = Key;
        using ValueType = Value;

        Node(Key key, Value value)
            : key{key}
            , value{value}
            , lh{nullptr}
            , rh{nullptr}
            , count{1}
        {
        }

        Key key;
        Value value;
        Node* lh;
        Node* rh;
        std::size_t count;
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
    find(const Key& key) const
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

    Node*
    put(Node* node, const Key& key, const Value& value)
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

    Node*
    eraseMin(Node* node)
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

    Node*
    eraseMax(Node* node)
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

    Node*
    min(Node* node) const
    {
        return node->lh ? min(node->lh) : node;
    }

    Node*
    max(Node* node) const
    {
        return node->rh ? max(node->rh) : node;
    }

    void
    keys(Node* node, KeysType& output, const Key& lo, const Key& hi) const
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

    Node*
    dropMin(Node* node)
    {
        if (!node->lh) {
            return node->rh;
        }
        node->lh = dropMin(node->lh);
        node->count = 1 + size(node->lh) + size(node->rh);
        return node;
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
