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
 * Represents the set of routes which are reachable from sourceOf vertex.
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
     * @param vertex - The target vertex
     *
     * @return @c true iff given vertex is reachable, @c false otherwise.
     */
    [[nodiscard]] bool
    hasRouteTo(std::size_t vertex) const;

    /**
     * Returns list of reachable vertices.
     *
     * @return The list of reachable vertices.
     */
    [[nodiscard]] Vertices
    reachability() const;

    /**
     * Returns total number of vertices.
     * @return The number of vertices.
     */
    [[nodiscard]] std::size_t
    verticesCount() const;

    /**
     * Creates route from given vertex to the start vertex.
     *
     * @param vertex - The target vertex
     *
     * @return The route from given vertex to the start vertex.
     */
    [[nodiscard]] Route
    routeTo(std::size_t vertex) const;

protected:
    explicit Routes(const Graph& graph);

protected:
    Marks marked;
    std::vector<long> edgeTo;
};

} // namespace algorithms
