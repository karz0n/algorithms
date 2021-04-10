#include "EdgeWeightedDigraph.hpp"

namespace algorithms {

EdgeWeightedDigraph::EdgeWeightedDigraph()
    : _edges{0}
{
}

EdgeWeightedDigraph::EdgeWeightedDigraph(std::size_t numberOfVertices)
    : _edges{0}
    , _forest{numberOfVertices}
{
}

void
EdgeWeightedDigraph::add(const DirectedEdge& edge)
{
    _edges++;

    _forest[edge.from()].push_front(edge);
}

const EdgeWeightedDigraph::DirectedEdgesList&
EdgeWeightedDigraph::adjacency(std::size_t v) const
{
    return _forest[v];
}

DirectedEdges
EdgeWeightedDigraph::edges() const
{
    DirectedEdges edges;
    for (const auto& edgeList : _forest) {
        for (const auto& edge : edgeList) {
            edges.push_back(edge);
        }
    }
    return edges;
}

std::size_t
EdgeWeightedDigraph::verticesCount() const
{
    return _forest.size();
}

std::size_t
EdgeWeightedDigraph::edgesCount() const
{
    return _edges;
}

void
EdgeWeightedDigraph::reset(std::size_t numberOfVertices)
{
    _edges = 0;
    Forest(numberOfVertices).swap(_forest);
}

bool
EdgeWeightedDigraph::empty() const
{
    return _forest.empty();
}

} // namespace algorithms