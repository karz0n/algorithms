#pragma once

#include <optional>
#include <functional>

namespace algorithms {

/**
 * Interval search tree implemenetation.
 */
template<typename Key, typename Value, typename Compare = std::less<Key>>
class IntervalSearchTree {
public:
    using ValueOrNull = std::optional<Value>;

    IntervalSearchTree()
        : _root{nullptr}
    {
    }

    void
    put(Key lo, Key hi, Value value)
    {
        _root = put(_root, lo, hi, value);
    }

    Value
    get(Key lo, Key hi) const
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        auto n = find(lo);
        if (!n) {
            throw std::runtime_error{"Item not found"};
        }
        return n->value;
    }

    void
    erase(Key lo, Key hi)
    {
        if (empty()) {
            throw std::runtime_error{"Tree is empty"};
        }
        _root = erase(_root, lo);
    }

    ValueOrNull
    intersects(Key lo, Key hi) const
    {
        Node* node = _root;
        while (node) {
            if (intersects(node->lo, node->hi, lo, hi)) {
                return ValueOrNull{node->value};
            }
            else if (!node->lh) {
                node = node->rh;
            }
            else if (compare(node->lh->max, lo) == -1) {
                node = node->rh;
            }
            else {
                node = node->lh;
            }
        }
        return std::nullopt;
    }

    bool
    empty() const
    {
        return !_root;
    }

private:
    struct Node {
        Node(const Key& lo, const Key& hi, const Value& value)
            : lo{lo}
            , hi{hi}
            , value{value}
            , lh{nullptr}
            , rh{nullptr}
            , max{hi}
        {
        }

        Key lo;
        Key hi;
        Key max;
        Value value;
        Node* lh;
        Node* rh;
    };

private:
    Node*
    put(Node* node, const Key& lo, const Key& hi, const Value& value)
    {
        if (!node) {
            return new Node{lo, hi, value};
        }

        auto c = compare(lo, node->lo);
        if (c == 0) {
            node->value = value;
        }
        else if (c < 0) {
            node->lh = put(node->lh, lo, hi, value);
            if (compare(node->max, node->lh->max) == -1) {
                node->max = node->lh->max;
            }
        }
        else if (c > 0) {
            node->rh = put(node->rh, lo, hi, value);
            if (compare(node->max, node->rh->max) == -1) {
                node->max = node->rh->max;
            }
        }

        return node;
    }

    Node*
    find(const Key& lo) const
    {
        Node* node = _root;
        while (node) {
            auto c = compare(lo, node->lo);
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
    erase(Node* node, const Key& lo)
    {
        if (!node) {
            return nullptr;
        }

        auto c = compare(lo, node->lo);
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
            node->lh = erase(node->lh, lo);
        }
        else if (c > 0) {
            node->rh = erase(node->rh, lo);
        }

        return node;
    }

    int
    compare(const Key& key1, const Key& key2) const
    {
        if (_compare(key1, key2)) {
            return -1;
        }
        if (_compare(key2, key1)) {
            return +1;
        }
        return 0;
    }

    Node*
    dropMin(Node* node)
    {
        if (!node->lh) {
            return node->rh;
        }
        node->lh = dropMin(node->lh);
        return node;
    }

    Node*
    min(Node* node) const
    {
        return node->lh ? min(node->lh) : node;
    }

    bool
    intersects(const Key& lo1, const Key& hi1, const Key& lo2, const Key& hi2) const
    {
        return (compare(hi2, lo1) >= 0 && compare(lo2, hi1) <= 0);
    }

private:
    Node* _root;
    Compare _compare;
};

} // namespace algorithms
