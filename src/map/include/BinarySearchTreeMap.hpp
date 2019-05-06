#ifndef BINARYSEARCHTREEMAP_HPP
#define BINARYSEARCHTREEMAP_HPP

#include <stdexcept>
#include <memory>

#include "Map.hpp"

namespace algorithms {

/**
 * Map implementation based on binary search tree.
 *
 * Efficiency of operation depends on randomness of inserted values and
 * their order. If input values will be inserted one by one in natural
 * order the effectiveness become equal N for search and insert, because
 * in this case we obtain simple linked list insead of binary tree.
 *
 *  - search - 1.39 lg N
 *  - insert - 1.39 lg N
 *  - search (guarantee) - N
 *  - insert (guarantee) - N
 *
 */
template <typename Key, typename Value, typename Comparator = std::less<Key>>
class BinarySearchTreeMap : public Map<Key, Value, Comparator> {
public:
    using KeyOrNull = typename Map<Key, Value, Comparator>::KeyOrNull;

    using ValueOrNull = typename Map<Key, Value, Comparator>::ValueOrNull;

    BinarySearchTreeMap()
    {
    }

    ~BinarySearchTreeMap()
    {
    }

    void put(const Key& key, Value&& value) override
    {
        _root = put(_root, key, std::forward<Value>(value));
    }

    Value& get(const Key& key) override
    {
        auto n = find(key);
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
        return n->value;
    }

    const Value& get(const Key& key) const override
    {
        auto n = find(key);
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
        return n->value;
    }

    ValueOrNull pick(const Key& key) const override
    {
        auto n = find(key);
        return n ? ValueOrNull{n->value} : std::nullopt;
    }

    bool contains(const Key& key) const override
    {
        return (find(key) != nullptr);
    }

    void erase(const Key& key) override
    {
        _root = erase(_root, key);
    }

    void eraseMin() override
    {
        if (_root) {
            _root = eraseMin(_root);
        }
    }

    void eraseMax() override
    {
        if (_root) {
            _root = eraseMax(_root);
        }
    }

    bool empty() const override
    {
        return !_root;
    }

    std::size_t size() const override
    {
        return size(_root);
    }

    std::size_t rank(const Key& key) const override
    {
        return rank(key, _root);
    }

    KeyOrNull min() const override
    {
        auto n = min(_root);
        return n ? KeyOrNull{n->key} : std::nullopt;
    }

    KeyOrNull max() const override
    {
        auto n = max(_root);
        return n ? KeyOrNull{n->key} : std::nullopt;
    }

    KeyOrNull floor(const Key& key) const override
    {
        auto n = floor(_root, key);
        return n ? KeyOrNull{n->key} : std::nullopt;
    }

    KeyOrNull ceiling(const Key& key) const override
    {
        auto n = ceiling(_root, key);
        return n ? KeyOrNull{n->key} : std::nullopt;
    }

private:
    struct Node {
        using Ptr = std::shared_ptr<Node>;

        Node(const Key& key, Value&& value)
            : key{key}
            , value{std::forward<Value>(value)}
            , count{1}
        {
        }

        Key key;
        Value value;
        Ptr left;
        Ptr right;
        std::size_t count;
    };

private:
    std::size_t size(typename Node::Ptr node) const
    {
        if (!node) {
            return 0;
        }
        return node->count;
    }

    int compare(const Key& k1, const Key& k2) const
    {
        if (_comparator(k1, k2)) {
            return -1;
        }
        if (_comparator(k2, k1)) {
            return +1;
        }
        return 0;
    }

    typename Node::Ptr find(const Key& key) const
    {
        typename Node::Ptr n = _root;
        while (n) {
            int cmp = compare(key, n->key);
            if (cmp < 0) {
                n = n->left;
            }
            else if (cmp > 0) {
                n = n->right;
            }
            else {
                return n;
            }
        }
        return nullptr;
    }

    typename Node::Ptr put(typename Node::Ptr node, const Key& key, Value&& value)
    {
        if (!node) {
            return std::make_shared<Node>(key, std::forward<Value>(value));
        }

        int cmp = compare(key, node->key);
        if (cmp < 0) {
            node->left = put(node->left, key, std::forward<Value>(value));
        }
        else if (cmp > 0) {
            node->right = put(node->right, key, std::forward<Value>(value));
        }
        else {
            node->value = std::forward<Value>(value);
        }
        node->count = 1 + size(node->left) + size(node->right);

        return node;
    }

    typename Node::Ptr floor(typename Node::Ptr node, const Key& key) const
    {
        if (!node) {
            return nullptr;
        }

        int cmp = compare(key, node->key);
        if (cmp < 0) {
            return floor(node->left, key);
        }
        else if (cmp > 0) {
            typename Node::Ptr t = floor(node->right, key);
            return t ? t : node;
        }
        else {
            return node;
        }
    }

    typename Node::Ptr ceiling(typename Node::Ptr node, const Key& key) const
    {
        if (!node) {
            return nullptr;
        }

        int cmp = compare(key, node->key);
        if (cmp < 0) {
            typename Node::Ptr t = ceiling(node->left, key);
            return t ? t : node;
        }
        else if (cmp > 0) {
            return ceiling(node->right, key);
        }
        else {
            return node;
        }
    }

    std::size_t rank(const Key& key, typename Node::Ptr node) const
    {
        if (!node) {
            return 0;
        }

        int cmp = compare(key, node->key);
        if (cmp < 0) {
            return rank(key, node->left);
        }
        else if (cmp > 0) {
            return 1 + size(node->left) + rank(key, node->right);
        }
        else {
            return size(node->left);
        }
    }

    typename Node::Ptr erase(typename Node::Ptr node, const Key& key)
    {
        if (!node) {
            return nullptr;
        }

        int cmp = compare(key, node->key);
        if (cmp < 0) {
            node->left = erase(node->left, key);
        }
        else if (cmp > 0) {
            node->right = erase(node->right, key);
        }
        else {
            if (!node->right) {
                return node->left;
            }

            typename Node::Ptr t = node;
            node = min(t->right);
            node->right = eraseMin(t->right);
            node->left = t->left;
        }
        node->count = 1 + size(node->left) + size(node->right);

        return node;
    }

    typename Node::Ptr eraseMin(typename Node::Ptr node)
    {
        if (!node->left) {
            return node->right;
        }
        node->left = eraseMin(node->left);
        node->count = 1 + size(node->left) + size(node->right);
        return node;
    }

    typename Node::Ptr eraseMax(typename Node::Ptr node)
    {
        if (!node->right) {
            return node->left;
        }
        node->right = eraseMax(node->right);
        node->count = 1 + size(node->left) + size(node->right);
        return node;
    }

    typename Node::Ptr min(typename Node::Ptr node) const
    {
        if (!node) {
            return nullptr;
        }
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    typename Node::Ptr max(typename Node::Ptr node) const
    {
        if (!node) {
            return nullptr;
        }
        while (node->right) {
            node = node->right;
        }
        return node;
    }

private:
    typename Node::Ptr _root;
    Comparator _comparator;
};

} // namespace algorithms

#endif // BINARYSEARCHTREEMAP_HPP
