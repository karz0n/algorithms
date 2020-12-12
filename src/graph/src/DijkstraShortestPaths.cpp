#include "DijkstraShortestPaths.hpp"

namespace algorithms {

DijkstraShortestPaths::DijkstraShortestPaths(const EdgeWeightedDigraph& graph, std::size_t s)
    : _edgeTo(graph.verticesCount())
    , _distTo(graph.verticesCount(), maxDistance())
{
    traverse(graph, s);
}

double
DijkstraShortestPaths::distanceTo(std::size_t v) const
{
    return _distTo[v];
}

DirectedEdges
DijkstraShortestPaths::pathTo(std::size_t v) const
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

DijkstraShortestPaths::EdgeOrNull
DijkstraShortestPaths::edgeTo(std::size_t v) const
{
    return _edgeTo[v];
}

bool
DijkstraShortestPaths::hasPathTo(std::size_t v) const
{
    return _edgeTo[v].has_value();
}

void
DijkstraShortestPaths::traverse(const EdgeWeightedDigraph& graph, std::size_t s)
{
    _distTo[s] = minDistance();

    Queue queue(graph.verticesCount());
    queue.push(s, minDistance());
    while (!queue.empty()) {
        const double v = queue.pop();
        for (const auto& edge : graph.adjacency(v)) {
            if (edge.weight() < minDistance()) {
                throw std::logic_error{"Only edge with non-negative weight allowed"};
            }
            relax(queue, edge);
        }
    }
}

void
DijkstraShortestPaths::relax(Queue& queue, const DirectedEdge& edge)
{
    const std::size_t v{edge.from()}, w{edge.to()};
    if (_distTo[w] > _distTo[v] + edge.weight() /* Better path has found */) {
        _distTo[w] = _distTo[v] + edge.weight();
        _edgeTo[w] = edge;
        queue.contains(w) ? queue.decreaseKey(w, _distTo[w]) // update path's weight
                          : queue.push(w, _distTo[w]);       // set path's weight
    }
}

} // namespace algorithms
