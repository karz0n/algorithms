#pragma once

#include <stack>
#include <functional>

namespace algorithms {

/**
 * Depth in-order traversal of tree without recursion.
 *
 * See full description in @file DepthInOrderTraverse.hpp
 */
template<typename Node>
class DepthInOrderNoRecTraverser {
public:
    using Callback = std::function<void(const typename Node::KeyType&, typename Node::ValueType&)>;

    explicit DepthInOrderNoRecTraverser(Node* root)
        : _root{root}
    {
    }

    void
    traverse(Callback callback)
    {
        if (!callback) {
            throw std::runtime_error{"Invalid callback object"};
        }
        traverse(_root, callback);
    }

private:
    void
    traverse(Node* node, const Callback& callback)
    {
        std::stack<Node*> nodes;
        while (node || !nodes.empty()) {
            while (node) {
                nodes.push(node);
                node = node->lh;
            }

            node = nodes.top();
            callback(node->key, node->value);
            nodes.pop();
            node = node->rh;
        }
    }

private:
    Node* _root;
};

} // namespace algorithms
