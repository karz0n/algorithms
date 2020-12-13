#include "AcyclicShortestPaths.hpp"

#include "TopologicalOrderIterator.hpp"

#include <stdexcept>

namespace algorithms {

AcyclicShortestPath::AcyclicShortestPath(const EdgeWeightedDigraph& graph,
                                         std::size_t s,
                                         bool shortest)
    : _edgeTo(graph.verticesCount())
    , _distTo(graph.verticesCount(), shortest ? maxDistance() : minDistance())
{
    traverse(graph, s, shortest);
}

double
AcyclicShortestPath::distanceTo(std::size_t v) const
{
    return _distTo[v];
}

DirectedEdges
AcyclicShortestPath::pathTo(std::size_t v) const
{
    if (!hasPathTo(v)) {
        throw std::logic_error{"No path exists"};
    }

    DirectedEdges path;
    for (auto edge = _edgeTo[v]; edge.has_value(); edge = _edgeTo[edge->from()]) {
        path.push_back(*edge);
    }
    return DirectedEdges(path.crbegin(), path.crend());
}

AcyclicShortestPath::EdgeOrNull
AcyclicShortestPath::edgeTo(std::size_t v) const
{
    return _edgeTo[v];
}

bool
AcyclicShortestPath::hasPathTo(std::size_t v) const
{
    return _edgeTo[v].has_value();
}

void
AcyclicShortestPath::traverse(const EdgeWeightedDigraph& graph, std::size_t s, bool shortest)
{
    _distTo[s] = minDistance();

    for (const std::size_t v : TopologicalOrderIterator(graph)) {
        for (const auto& edge : graph.adjacency(v)) {
            relax(edge, shortest);
        }
    }
}

void
AcyclicShortestPath::relax(const DirectedEdge& edge, bool shortest)
{
    const std::size_t v{edge.from()}, w{edge.to()};

    bool betterPathFound = shortest ? _distTo[w] > _distTo[v] + edge.weight()
                                    : _distTo[w] < _distTo[v] + edge.weight();

    if (betterPathFound) {
        _distTo[w] = _distTo[v] + edge.weight();
        _edgeTo[w] = edge;
    }
}

} // namespace algorithms