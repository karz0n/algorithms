#include "TernarySearchTries.hpp"

#include <stdexcept>

namespace algorithms {

TernarySearchTries::TernarySearchTries()
    : _root{nullptr}
{
}

TernarySearchTries::~TernarySearchTries()
{
    clear();
}

bool
TernarySearchTries::has(std::string_view key)
{
    const auto* node = get(_root, key, 0);
    return node && node->value.has_value();
}

int
TernarySearchTries::get(std::string_view key)
{
    const Node* node = get(_root, key, 0);
    if (!node) {
        throw std::runtime_error{"Element is absent"};
    }
    return node->value.value();
}

void
TernarySearchTries::put(std::string_view key, int value)
{
    _root = put(_root, key, value, 0);
}

TernarySearchTries::Keys
TernarySearchTries::keys() const
{
    Keys keys;
    std::string prefix;
    collect(_root, prefix, keys);
    return keys;
}

TernarySearchTries::Keys
TernarySearchTries::keysWithPrefix(std::string_view prefix) const
{
    const auto* root = get(_root, prefix, 0);
    Keys keys;
    if (root) {
        if (root->value) {
            keys.emplace_back(prefix);
        }

        std::string pre{prefix};
        collect(root->mi, pre, keys);
    }
    return keys;
}

TernarySearchTries::Keys
TernarySearchTries::keysThatMatch(std::string_view pattern) const
{
    Keys keys;
    std::string pre;
    collect(_root, pre, pattern, 0, keys);
    return keys;
}

std::string
TernarySearchTries::longestPrefixOf(std::string_view prefix) const
{
    const auto length = search(_root, prefix, 0, 0);
    return std::string(prefix.substr(0, length));
}

void
TernarySearchTries::erase(std::string_view key)
{
    _root = erase(_root, key, 0);
}

void
TernarySearchTries::clear()
{
    if (_root) {
        delete _root, _root = nullptr;
    }
}

TernarySearchTries::Node*
TernarySearchTries::put(Node* node, std::string_view key, int value, std::size_t dimension)
{
    const char ch = key[dimension];
    if (!node) {
        node = new Node{ch};
    }

    if (ch < node->ch) {
        node->lh = put(node->lh, key, value, dimension);
        return node;
    }
    if (ch > node->ch) {
        node->rh = put(node->rh, key, value, dimension);
        return node;
    }

    if (key.size() == dimension + 1) {
        node->value = value;
    } else {
        node->mi = put(node->mi, key, value, dimension + 1);
    }
    return node;
}

TernarySearchTries::Node*
TernarySearchTries::get(Node* node, std::string_view key, std::size_t dimension) const
{
    if (!node) {
        return nullptr;
    }

    const char ch = key[dimension];
    if (ch < node->ch) {
        return get(node->lh, key, dimension);
    }
    if (ch > node->ch) {
        return get(node->rh, key, dimension);
    }

    if (key.size() == dimension + 1) {
        return node;
    } else {
        return get(node->mi, key, dimension + 1);
    }
}

std::size_t
TernarySearchTries::search(Node* node,
                           std::string_view key,
                           std::size_t dimension,
                           std::size_t length) const
{
    if (!node) {
        return length;
    }

    const char ch = key[dimension];
    if (ch < node->ch) {
        return search(node->lh, key, dimension, length);
    }
    if (ch > node->ch) {
        return search(node->rh, key, dimension, length);
    }

    if (node->value) {
        length = dimension + 1;
    }

    if (key.size() == dimension + 1) {
        return length;
    } else {
        return search(node->mi, key, dimension + 1, length);
    }
}

void
TernarySearchTries::collect(Node* node, std::string& prefix, Keys& keys) const
{
    if (!node) {
        return;
    }

    collect(node->lh, prefix, keys);
    if (node->value) {
        keys.push_back(prefix + node->ch);
    }
    collect(node->mi, prefix += node->ch, keys);
    prefix.pop_back();
    collect(node->rh, prefix, keys);
}

void
TernarySearchTries::collect(Node* node,
                            std::string& prefix,
                            std::string_view pattern,
                            std::size_t dimension,
                            Keys& keys) const
{
    if (!node) {
        return;
    }

    const char ch = pattern[dimension];
    if (ch == '.' || ch < node->ch) {
        collect(node->lh, prefix, pattern, dimension, keys);
    }
    if (ch == '.' || ch == node->ch) {
        const std::size_t minOne = pattern.size() - 1;
        if (dimension == minOne && node->value) {
            keys.push_back(prefix + node->ch);
        }
        if (dimension < minOne) {
            collect(node->mi, prefix += node->ch, pattern, dimension + 1, keys);
            prefix.pop_back();
        }
    }
    if (ch == '.' || ch > node->ch) {
        collect(node->rh, prefix, pattern, dimension, keys);
    }
}

TernarySearchTries::Node*
TernarySearchTries::erase(Node* node, std::string_view key, std::size_t dimension)
{
    if (!node) {
        return nullptr;
    }

    const auto ch = key[dimension];
    if (ch < node->ch) {
        node->lh = erase(node->lh, key, dimension);
    }
    if (ch > node->ch) {
        node->rh = erase(node->rh, key, dimension);
    }

    if (key.size() == dimension + 1) {
        node->value.reset();
    } else {
        node->mi = erase(node->mi, key, dimension + 1);
    }

    if (!(node->hasChildren() || node->hasValue())) {
        delete node, node = nullptr;
    }

    return node;
}

} // namespace algorithms
