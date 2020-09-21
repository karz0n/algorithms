#pragma once

#include "Types.hpp"
#include "Graph.hpp"

#include <vector>

namespace algorithms {

/**
 * The route as a list of vertex.
 */
using Route = std::vector<std::size_t>;

/**
 * The basic class of graph routes.
 *
 * Represents the set of routes which are reachable from source vertex.
 * Particular implementation presents in derived classes.
 *
 * @see DepthFirstRoutes
 * @see BreadthFirstRoutes
 */
class Routes {
public:
    virtual ~Routes() = default;

    /**
     * Checks if given vertex reachable from start vertex.
     *
     * @param v - The target vertex
     *
     * @return @c true iff given vertex is reachable, @c false otherwise.
     */
    [[nodiscard]] bool
    hasRouteTo(std::size_t v) const;

    /**
     * Create route from given vertex to the start vertex.
     *
     * @param v - The target vertex
     *
     * @return The route from given vertex to the start vertex.
     */
    [[nodiscard]] Route
    routeTo(std::size_t v) const;

protected:
    Routes(const Graph& graph, std::size_t s);

protected:
    Marks marks;
    std::vector<std::size_t> source;
};

} // namespace algorithms
