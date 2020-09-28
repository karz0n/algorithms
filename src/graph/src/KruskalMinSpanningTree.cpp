#include "KruskalMinSpanningTree.hpp"

#include <PriorityQueue.hpp>
#include <UnionFind.hpp>

namespace algorithms {

KruskalMinSpanningTree::KruskalMinSpanningTree(const EdgeWeightedGraph& graph)
    : _weight{}
{
    traverse(graph);
}

const KruskalMinSpanningTree::Edges&
KruskalMinSpanningTree::edges() const
{
    return _edges;
}

double
KruskalMinSpanningTree::weight() const
{
    return _weight;
}

void
KruskalMinSpanningTree::traverse(const EdgeWeightedGraph& graph)
{
    MinPriorityQueue<Edge> queue;
    for (const auto& edge : graph.edges()) {
        queue.push(edge);
    }

    UnionFind uf{graph.verticesCount()};
    while (!queue.empty() && _edges.size() < graph.verticesCount() - 1) {
        const auto edge = queue.pop();
        const std::size_t v = edge.either();
        const std::size_t w = edge.other(v);
        if (!uf.connected(v, w)) {
            _edges.push_back(edge);
            uf.associate(v, w);
        }
    }
}

} // namespace algorithms