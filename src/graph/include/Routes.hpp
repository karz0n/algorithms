#pragma once

#include "Graph.hpp"

#include <vector>

namespace algorithms {

/**
 * The route as a list of vertex.
 */
using Route = std::vector<std::size_t>;

/**
 * The basic class of graph routes.
 */
class Routes {
public:
    virtual ~Routes() = default;

    /**
     * Checks if given vertex reachable from start vertex.
     *
     * @param v - The target vertex
     *
     * @return \c true iff given vertex is reachable, \c false otherwise.
     */
    bool
    hasRouteTo(std::size_t v) const;

    /**
     * Create route from given vertex to the start vertex.
     *
     * @param v - The target vertex
     *
     * @return The route from given vertex to the start vertex.
     */
    Route
    routeTo(std::size_t v) const;

protected:
    Routes(const Graph& graph, std::size_t s);

protected:
    std::vector<bool> marked;
    std::vector<std::size_t> edgeTo;
};

} // namespace algorithms
