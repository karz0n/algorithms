#pragma once

#include <functional>

namespace algorithms {

/**
 * Depth post-order traversal of tree using recursion.
 *
 * Order: (Root, Left, Right)
 *  - Traverse the left subtree
 *  - Traverse the right subtree
 *  - Visit the root
 *
 * Used to delete the tree. Also useful to get the postfix expression.
 */
template<typename Node>
class DepthPostOrderTraverser {
public:
    using Callback = std::function<void(const typename Node::KeyType&, typename Node::ValueType&)>;

    DepthPostOrderTraverser(Node* root)
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
        if (!node) {
            return;
        }

        traverse(node->lh, callback);
        traverse(node->rh, callback);
        callback(node->key, node->value);
    }

private:
    Node* _root;
};

} // namespace algorithms
