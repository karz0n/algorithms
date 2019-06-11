#ifndef REDBLACKBINARYSEARCHTREEMAP_HPP
#define REDBLACKBINARYSEARCHTREEMAP_HPP

#include <stdexcept>
#include <memory>

#include "Map.hpp"

/**
 *
 * Invariants:
 *  - No node has two red link connected to it
 *  - Every path from root to null link has the same number of black links (perfect black balance)
 *  - Red link lean left
 *
 */
namespace algorithms {

template <typename Key, typename Value, typename Comparator = std::less<Key>>
class RedBlackBinarySearchTreeMap : public Map<Key, Value, Comparator> {
public:
    using KeyOrNull = typename Map<Key, Value, Comparator>::KeyOrNull;

    using ValueOrNull = typename Map<Key, Value, Comparator>::ValueOrNull;

    RedBlackBinarySearchTreeMap()
    {
    }

    ~RedBlackBinarySearchTreeMap()
    {
    }

    void put(const Key& key, Value&& value) override
    {
        _root = put(_root, key, std::forward<Value>(value));
        _root->color = Node::Colors::black;
    }

    Value& get(const Key& key) override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        auto n = find(key);
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
        return n->value;
    }

    const Value& get(const Key& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
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
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        if (!contains(key)) {
            return;
        }

        if (!isRed(_root->left) && !isRed(_root->right)) {
            _root->color = Node::Colors::red;
        }
        _root = erase(_root, key);
        if (!empty()) {
            _root->color = Node::Colors::black;
        }
    }

    void eraseMin() override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }

        if (!isRed(_root->left) && !isRed(_root->right)) {
            _root->color = Node::Colors::red;
        }
        _root = eraseMin(_root);
        if (!empty()) {
            _root->color = Node::Colors::black;
        }
    }

    void eraseMax() override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }

        if (!isRed(_root->left) && !isRed(_root->right)) {
            _root->color = Node::Colors::red;
        }
        _root = eraseMax(_root);
        if (!empty()) {
            _root->color = Node::Colors::black;
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
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        auto n = floor(_root, key);
        return n ? KeyOrNull{n->key} : std::nullopt;
    }

    KeyOrNull ceiling(const Key& key) const override
    {
        if (empty()) {
            throw std::runtime_error{"Map is empty"};
        }
        auto n = ceiling(_root, key);
        return n ? KeyOrNull{n->key} : std::nullopt;
    }

private:
    struct Node {
        using Ptr = std::shared_ptr<Node>;

        enum class Colors { red = true, black = false };

        Node(const Key& key, Value&& value)
            : key{key}
            , value{std::forward<Value>(value)}
            , count{1}
            , color{Colors::red} /* New link is RED by default */
        {
        }

        Key key;
        Value value;
        Ptr left;
        Ptr right;
        std::size_t count;
        Colors color;
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

    NodePtr put(NodePtr node, const Key& key, Value&& value)
    {
        if (!node) {
            return std::make_shared<Node>(key, std::forward<Value>(value));
        }

        /** Put node as usual */
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

        /** Balance 2-3 node (red-black tree) */
        if (isRed(node->right) && !isRed(node->left)) {
            node = rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left)) {
            node = rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right)) {
            flipColors(node);
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
        auto c = compare(key, node->key);
        if (c < 0) {
            if (!isRed(node->left) && !isRed(node->left->left)) {
                node = moveRedLeft(node);
            }
            node->left = erase(node->left, key);
        }
        else {
            if (isRed(node->left)) {
                node = rotateRight(node);
            }
            if (compare(key, node->key) == 0 && !node->right) {
                return nullptr;
            }
            if (!isRed(node->right) && !isRed(node->right->left)) {
                node = moveRedRight(node);
            }
            if (compare(key, node->key) == 0) {
                auto x = min(node->right);
                node->key = x->key;
                node->value = x->value;
                node->right = eraseMin(node->right);
            }
            else {
                node->right = erase(node->right, key);
            }
        }
        return balance(node);
    }

    NodePtr eraseMin(NodePtr node)
    {
        if (!node->left) {
            return nullptr;
        }
        if (!isRed(node->left) && !isRed(node->left->left)) {
            node = moveRedLeft(node);
        }
        node->left = eraseMin(node->left);
        return balance(node);
    }

    NodePtr eraseMax(NodePtr node)
    {
        if (isRed(node->left)) {
            node = rotateRight(node);
        }
        if (!node->right) {
            return nullptr;
        }
        if (!isRed(node->right) && !isRed(node->right->right)) {
            node = moveRedRight(node);
        }
        node->right = eraseMax(node->right);
        return balance(node);
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

    NodePtr min(NodePtr node) const
    {
        return (node->left) ? min(node->left) : node;
    }

    NodePtr max(NodePtr node) const
    {
        return (node->right) ? max(node->right) : node;
    }

    NodePtr rotateLeft(NodePtr node)
    {
#ifndef NDEBUG
        if (!node) {
            throw std::invalid_argument("Invalid link object");
        }
        if (!isRed(node->right)) {
            throw std::logic_error("Right link should be red");
        }
#endif
        NodePtr x = node->right;
        node->right = x->left;
        x->left = node;
        x->color = x->left->color;
        x->left->color = Node::Colors::red;
        x->count = node->count;
        node->count = size(node->left) + size(node->right) + 1;
        return x;
    }

    NodePtr rotateRight(NodePtr node)
    {
#ifndef NDEBUG
        if (!node) {
            throw std::invalid_argument("Invalid link object");
        }
        if (!isRed(node->left)) {
            throw std::logic_error("Left link should be red");
        }
#endif
        NodePtr x = node->left;
        node->left = x->right;
        x->right = node;
        x->color = x->right->color;
        x->right->color = Node::Colors::red;
        x->count = node->count;
        node->count = size(node->left) + size(node->right) + 1;
        return x;
    }

    void flipColors(NodePtr node)
    {
#ifndef NDEBUG
        if (!node || !node->left || !node->right) {
            throw std::invalid_argument("Invalid links object");
        }
        if (isRed(node) && (isRed(node->left) || isRed(node->right))) {
            throw std::logic_error("Parent link should be black");
        }
        if (!isRed(node) && (!isRed(node->left) || !isRed(node->right))) {
            throw std::logic_error("Left and right links should be red");
        }
#endif
        node->color = (node->color == Node::Colors::red) ? Node::Colors::black : Node::Colors::red;
        node->left->color = (node->left->color == Node::Colors::red) ? Node::Colors::black : Node::Colors::red;
        node->right->color = (node->right->color == Node::Colors::red) ? Node::Colors::black : Node::Colors::red;
    }

    NodePtr balance(NodePtr node)
    {
        if (isRed(node->right)) {
            node = rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left)) {
            node = rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right)) {
            flipColors(node);
        }
        node->count = size(node->left) + size(node->right) + 1;
        return node;
    }

    NodePtr moveRedLeft(NodePtr node)
    {
        flipColors(node);
        if (isRed(node->right->left)) {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
            flipColors(node);
        }
        return node;
    }

    NodePtr moveRedRight(NodePtr node)
    {
        flipColors(node);
        if (isRed(node->left->left)) {
            node = rotateRight(node);
            flipColors(node);
        }
        return node;
    }

    bool isRed(NodePtr node) const
    {
        return node ? (node->color == Node::Colors::red) : false;
    }

private:
    NodePtr _root;
    Comparator _comparator;
};

} // namespace algorithms

#endif // REDBLACKBINARYSEARCHTREEMAP_HPP
