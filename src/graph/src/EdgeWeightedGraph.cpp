#include "EdgeWeightedGraph.hpp"

namespace algorithms {

EdgeWeightedGraph::EdgeWeightedGraph()
    : _edges{0}
{
}

EdgeWeightedGraph::EdgeWeightedGraph(std::size_t numberOfVertices)
    : _edges{0}
    , _forest{numberOfVertices}
{
}

void
EdgeWeightedGraph::add(const Edge& edge)
{
    _edges++;

    std::size_t v = edge.either();
    std::size_t w = edge.other(v);

    _forest[v].push_front(edge);
    _forest[w].push_front(edge);
}

const EdgeWeightedGraph::Edges&
EdgeWeightedGraph::adjacency(std::size_t v) const
{
    return _forest[v];
}

EdgeWeightedGraph::Edges
EdgeWeightedGraph::edges() const
{
    Edges edges;
    for (const auto& v : _forest) {
        for (const auto& edge : v) {
            edges.push_front(edge);
        }
    }
    return edges;
}

std::size_t
EdgeWeightedGraph::verticesCount() const
{
    return _forest.size();
}

std::size_t
EdgeWeightedGraph::edgesCount() const
{
    return _edges;
}

void
EdgeWeightedGraph::reset(std::size_t numberOfVertices)
{
    _edges = 0;
    Forest(numberOfVertices).swap(_forest);
}

bool
EdgeWeightedGraph::empty() const
{
    return _forest.empty();
}

} // namespace algorithms
