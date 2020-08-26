#pragma once

#include <functional>

namespace algorithms {

/**
 * Depth in-order traversal of tree using recursion.
 *
 * Order: (Root, Left, Right)
 *  - Traverse the left subtree
 *  - Visit the root
 *  - Traverse the right subtree
 *
 * Used to get nodes in non-decreasing order (x[n+1] >= x[n]).
 * To get nodes in non-increasing order (x[n+1] <= x[n]), a variation
 * of in-order traverse where it's reversed can be used.
 */
template<typename Node>
class DepthInOrderTraverser {
public:
    using Callback = std::function<void(const typename Node::KeyType&, typename Node::ValueType&)>;

    explicit DepthInOrderTraverser(Node* root)
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
        if (!node) {
            return;
        }

        traverse(node->lh, callback);
        callback(node->key, node->value);
        traverse(node->rh, callback);
    }

private:
    Node* _root;
};

} // namespace algorithms
