#include "KruskalMinSpanningTree.hpp"

#include <PriorityQueue.hpp>
#include <UnionFind.hpp>

namespace algorithms {

KruskalMinSpanningTree::KruskalMinSpanningTree(const EdgeWeightedGraph& graph)
    : _weight{0.0}
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

    UnionFind unions{graph.verticesCount()};
    while (!queue.empty() && _edges.size() < graph.verticesCount() - 1) {
        const auto edge = queue.pop();
        const std::size_t v = edge.either();
        const std::size_t w = edge.other(v);
        if (unions.find(v) != unions.find(w)) {
            unions.associate(v, w);
            _edges.push_back(edge);
            _weight += edge.weight();
        }
    }
}

} // namespace algorithms