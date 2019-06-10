#ifndef BINARYSEARCHTREEMAP_HPP
#define BINARYSEARCHTREEMAP_HPP

#ifndef NDEBUG
#include <stdexcept>
#endif
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
#ifndef NDEBUG
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
#endif
        return n->value;
    }

    const Value& get(const Key& key) const override
    {
        auto n = find(key);
#ifndef NDEBUG
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
#endif
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

    Key min() const override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        return min(_root)->key;
    }

    Key max() const override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        return max(_root)->key;
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

    using NodePtr = typename Node::Ptr;

private:
    std::size_t size(NodePtr node) const
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

    NodePtr find(const Key& key) const
    {
        NodePtr n = _root;
        while (n) {
            auto c = compare(key, n->key);
            if (c == 0) {
                return n;
            }
            else if (c < 0) {
                n = n->left;
            }
            else if (c > 0) {
                n = n->right;
            }
        }
        return nullptr;
    }

    NodePtr put(NodePtr node, const Key& key, Value&& value)
    {
        if (!node) {
            return std::make_shared<Node>(key, std::forward<Value>(value));
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            node->value = std::forward<Value>(value);
        }
        else if (c < 0) {
            node->left = put(node->left, key, std::forward<Value>(value));
        }
        else if (c > 0) {
            node->right = put(node->right, key, std::forward<Value>(value));
        }
        node->count = 1 + size(node->left) + size(node->right);

        return node;
    }

    NodePtr floor(NodePtr node, const Key& key) const
    {
        if (!node) {
            return nullptr;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            return node;
        }
        if (c < 0) {
            return floor(node->left, key);
        }
        if (c > 0) {
            NodePtr t = floor(node->right, key);
            return t ? t : node;
        }

        return nullptr;
    }

    NodePtr ceiling(NodePtr node, const Key& key) const
    {
        if (!node) {
            return nullptr;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            return node;
        }
        if (c < 0) {
            NodePtr t = ceiling(node->left, key);
            return t ? t : node;
        }
        if (c > 0) {
            return ceiling(node->right, key);
        }

        return nullptr;
    }

    std::size_t rank(const Key& key, NodePtr node) const
    {
        if (!node) {
            return 0;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            return size(node->left);
        }
        if (c < 0) {
            return rank(key, node->left);
        }
        if (c > 0) {
            return 1 + size(node->left) + rank(key, node->right);
        }

        return 0;
    }

    NodePtr erase(NodePtr node, const Key& key)
    {
        if (!node) {
            return nullptr;
        }

        auto c = compare(key, node->key);
        if (c == 0) {
            if (!node->right) {
                return node->left;
            }

            NodePtr t = node;
            node = min(t->right);
            node->right = eraseMin(t->right);
            node->left = t->left;
        }
        else if (c < 0) {
            node->left = erase(node->left, key);
        }
        else if (c > 0) {
            node->right = erase(node->right, key);
        }
        node->count = 1 + size(node->left) + size(node->right);

        return node;
    }

    NodePtr eraseMin(NodePtr node)
    {
        if (!node->left) {
            return node->right;
        }
        node->left = eraseMin(node->left);
        node->count = 1 + size(node->left) + size(node->right);
        return node;
    }

    NodePtr eraseMax(NodePtr node)
    {
        if (!node->right) {
            return node->left;
        }
        node->right = eraseMax(node->right);
        node->count = 1 + size(node->left) + size(node->right);
        return node;
    }

    NodePtr min(NodePtr node) const
    {
        return (node->left) ? min(node->left) : node;
    }

    NodePtr max(NodePtr node) const
    {
        return (node->right) ? max(node->right) : node;
    }

private:
    NodePtr _root;
    Comparator _comparator;
};

} // namespace algorithms

#endif // BINARYSEARCHTREEMAP_HPP
