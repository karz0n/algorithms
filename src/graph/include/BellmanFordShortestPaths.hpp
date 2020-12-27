#pragma once

#include "Types.hpp"
#include "EdgeWeightedDigraph.hpp"

#include <optional>

namespace algorithms {

/**
 * Find shortest paths from given vertex using BellmanFord's algorithm.
 *
 * Short overview of BellmanFord's algorithm:
 *  - consider all vertices from given vertex s
 *  - relax each edge
 *  - check for negative cycle with cost amortization
 *
 * Note: edges with negative weight can exists
 */
class BellmanFordShortestPaths {
public:
    using EdgeOrNull = std::optional<DirectedEdge>;

    BellmanFordShortestPaths(const EdgeWeightedDigraph& graph, std::size_t s);

    [[nodiscard]]
    double distanceTo(std::size_t v) const;

    [[nodiscard]]
    DirectedEdges pathTo(std::size_t v) const;

    [[nodiscard]]
    EdgeOrNull edgeTo(std::size_t v) const;

    [[nodiscard]]
    bool hasPathTo(std::size_t v) const;

    [[nodiscard]]
    bool hasNegativeCycle() const;

    [[nodiscard]]
    const Vertices& negativeCycle() const;

    static double minDistance();

    static double maxDistance();

private:
    void traverse(const EdgeWeightedDigraph& graph, std::size_t s);

    bool relax(const DirectedEdge& edge);

    void findCycle();

private:
    std::vector<EdgeOrNull> _edgeTo;
    std::vector<double> _distTo;
    Vertices _cycle;
};

//
// Inlines
//

inline double BellmanFordShortestPaths::minDistance()
{
    return 0.0;
}

inline double BellmanFordShortestPaths::maxDistance()
{
    return std::numeric_limits<double>::max();
}

}