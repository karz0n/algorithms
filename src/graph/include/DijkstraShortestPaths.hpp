#pragma once

#include "Types.hpp"
#include "EdgeWeightedDigraph.hpp"
#include "IndexPriorityQueue.hpp"

#include <optional>

namespace algorithms {

/**
 * Find shortest paths from given vertex using Dijkstra's algorithm.
 *
 * Short overview of Dijkstra's algorithm:
 *  - consider vertices in increasing order of distance from s
 *    (non-tree vertex with the lowest distTo[v] value)
 *  - add vertex to tree and relax all edges pointing from that vertex
 *
 * Main goal - compute SPT (shortest path tree) from given vertex by two actions:
 *  - repeat until optimality conditions are satisfied:
 *      - distTo[v] - the length of path from s to v
 *      - e = v -> w, distTo[w] <= distTo[v] + e.weight()
 *  - relax edge
 *
 * Note: no-negative weights must exists
 */
class DijkstraShortestPaths {
public:
    using EdgeOrNull = std::optional<DirectedEdge>;
    using Queue = IndexMinPriorityQueue<double>;

    DijkstraShortestPaths(const EdgeWeightedDigraph& graph, std::size_t s);

    [[nodiscard]]
    double distanceTo(std::size_t v) const;

    [[nodiscard]]
    DirectedEdges pathTo(std::size_t v) const;

    [[nodiscard]]
    EdgeOrNull edgeTo(std::size_t v) const;

    [[nodiscard]]
    bool hasPathTo(std::size_t v) const;

    static double minDistance();

    static double maxDistance();

private:
    void traverse(const EdgeWeightedDigraph& graph, std::size_t s);

    void relax(Queue& queue, const DirectedEdge& edge);

private:
    std::vector<EdgeOrNull> _edgeTo;
    std::vector<double> _distTo;
};

//
// Inlines
//

inline double DijkstraShortestPaths::minDistance()
{
    return 0.0;
}

inline double DijkstraShortestPaths::maxDistance()
{
    return std::numeric_limits<double>::max();
}

}

