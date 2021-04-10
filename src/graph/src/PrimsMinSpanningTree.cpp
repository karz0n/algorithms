#include "PrimsMinSpanningTree.hpp"

#include "IndexPriorityQueue.hpp"

#include <optional>
#include <limits>

namespace algorithms {

PrimsMinSpanningTree::PrimsMinSpanningTree(const EdgeWeightedGraph& graph)
    : _weight{0.0}
{
    traverse(graph);
}

const Edges&
PrimsMinSpanningTree::edges() const
{
    return _edges;
}

double
PrimsMinSpanningTree::weight() const
{
    return _weight;
}

void
PrimsMinSpanningTree::traverse(const EdgeWeightedGraph& graph)
{
    Marks marks(graph.verticesCount(), false);
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        if (!marks[v]) {
            traverse(graph, marks, v);
        }
    }
}

void
PrimsMinSpanningTree::traverse(const EdgeWeightedGraph& graph, Marks& marks, std::size_t v)
{
    using EdgeOrNull = std::optional<Edge>;
    using EdgesQueue = IndexMinPriorityQueue<double>;

    static const double MinDistance = 0.0;
    static const double MaxDistance = std::numeric_limits<double>::max();

    std::vector<EdgeOrNull> edgeTo(graph.verticesCount());
    std::vector<double> distTo(graph.verticesCount(), MaxDistance);
    distTo[v] = MinDistance;

    EdgesQueue queue{graph.verticesCount()};
    queue.push(v, MinDistance);
    while (!queue.empty()) {
        v = queue.pop();
        marks[v] = true;
        /* Iterate over all not visited adjacency vertices and save path to them */
        for (const auto& edge : graph.adjacency(v)) {
            std::size_t w = edge.other(v);
            if (marks[w]) {
                continue;
            }

            /* Check existing path to vertex */
            if (edge.weight() < distTo[w]) {
                edgeTo[w] = edge;
                distTo[w] = edge.weight();
                if (queue.contains(w)) {
                    queue.decreaseKey(w, distTo[w]);
                } else {
                    queue.push(w, distTo[w]);
                }
            }
        }
    }

    for (const auto& edge : edgeTo) {
        if (edge) {
            _weight += edge->weight();
            _edges.push_back(*edge);
        }
    }
}

} // namespace algorithms
