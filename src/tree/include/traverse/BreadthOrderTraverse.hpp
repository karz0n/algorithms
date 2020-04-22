#pragma once

#include <queue>
#include <functional>

namespace algorithms {

/**
 * Breadth order traversal of tree.
 *
 *
 */
template<typename Node>
class BreadthOrderTraverser {
public:
    using Callback = std::function<void(const typename Node::KeyType&, typename Node::ValueType&)>;

    BreadthOrderTraverser(Node* root)
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

        std::queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            auto e = q.front();
            callback(e->key, e->value);
            if (e->lh) {
                q.push(e->lh);
            }
            if (e->rh) {
                q.push(e->rh);
            }
            q.pop();
        }
    }

private:
    Node* _root;
};

} // namespace algorithms
