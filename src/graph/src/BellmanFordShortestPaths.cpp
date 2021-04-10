#include "BellmanFordShortestPaths.hpp"

#include "DirectedCycleFinder.hpp"

#include <stdexcept>
#include <queue>

namespace algorithms {

BellmanFordShortestPaths::BellmanFordShortestPaths(const EdgeWeightedDigraph& graph, std::size_t s)
    : _edgeTo(graph.verticesCount())
    , _distTo(graph.verticesCount(), maxDistance())
{
    traverse(graph, s);
}

double
BellmanFordShortestPaths::distanceTo(std::size_t v) const
{
    return _distTo[v];
}

DirectedEdges
BellmanFordShortestPaths::pathTo(std::size_t v) const
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

BellmanFordShortestPaths::EdgeOrNull
BellmanFordShortestPaths::edgeTo(std::size_t v) const
{
    return _edgeTo[v];
}

bool
BellmanFordShortestPaths::hasPathTo(std::size_t v) const
{
    return _edgeTo[v].has_value();
}

bool
BellmanFordShortestPaths::hasNegativeCycle() const
{
    return !_cycle.empty();
}

const Vertices&
BellmanFordShortestPaths::negativeCycle() const
{
    return _cycle;
}

void
BellmanFordShortestPaths::traverse(const EdgeWeightedDigraph& graph, std::size_t s)
{
    _distTo[s] = minDistance();

    Marks marks(graph.verticesCount());
    std::queue<std::size_t> updatePool;
    updatePool.push(s);
    marks[s] = true;

    std::size_t cost{0};
    while (!updatePool.empty() && !hasNegativeCycle()) {
        const std::size_t v{updatePool.front()};
        updatePool.pop();
        marks[v] = false;

        for (const auto& edge : graph.adjacency(v)) {
            const std::size_t w{edge.to()};
            if (relax(edge) && !marks[w]) {
                updatePool.push(w);
                marks[w] = true;
            }
            if (++cost % graph.verticesCount() == 0 /* Find cycle on each vertex count step */) {
                findCycle();
                if (hasNegativeCycle()) {
                    return;
                }
            }
        }
    }
}

bool
BellmanFordShortestPaths::relax(const DirectedEdge& edge)
{
    const std::size_t v{edge.from()}, w{edge.to()};
    if (_distTo[w] > _distTo[v] + edge.weight() + std::numeric_limits<double>::epsilon()) {
        _distTo[w] = _distTo[v] + edge.weight();
        _edgeTo[w] = edge;
        return true;
    }
    return false;
}

void
BellmanFordShortestPaths::findCycle()
{
    EdgeWeightedDigraph graph{_edgeTo.size()};
    for (const auto& edge : _edgeTo) {
        if (edge) {
            graph.add(*edge);
        }
    }

    DirectedCycleFinder finder{graph};
    _cycle = finder.cycle();
}

} // namespace algorithms