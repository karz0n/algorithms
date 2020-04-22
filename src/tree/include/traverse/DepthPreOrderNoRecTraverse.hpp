#pragma once

#include <stack>
#include <functional>

namespace algorithms {

/**
 * Depth pre-order traversal of tree without recursion.
 *
 * See full description in @file DepthPostOrderTraverse.hpp
 */
template<typename Node>
class DepthPreOrderNoRecTraverser {
public:
    using Callback = std::function<void(const typename Node::KeyType&, typename Node::ValueType&)>;

    DepthPreOrderNoRecTraverser(Node* root)
        : _root{root}
    {
    }

    void
    traverse(Callback callback)
    {
        if (!callback) {
            std::runtime_error{"Invalid callback object"};
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
                callback(node->key, node->value);
                nodes.push(node);
                node = node->lh;
            }

            node = nodes.top();
            nodes.pop();
            node = node->rh;
        }
    }

private:
    Node* _root;
};

} // namespace algorithms
