#pragma once

#include <functional>

namespace algorithms {

/**
 * Depth pre-order traversal of tree using recursion.
 *
 * Order: (Root, Left, Right)
 *  - Visit the root
 *  - Traverse the left subtree
 *  - Traverse the right subtree
 *
 * Used to create a copy of the tree (in the same order as was inserted).
 */
template<typename Node>
class DepthPreOrderTraverser {
public:
    using Callback = std::function<void(const typename Node::KeyType&, typename Node::ValueType&)>;

    DepthPreOrderTraverser(Node* root)
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

        callback(node->key, node->value);
        traverse(node->lh, callback);
        traverse(node->rh, callback);
    }

private:
    Node* _root;
};

} // namespace algorithms
