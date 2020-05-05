#pragma once

#include "Graph.hpp"

#include <vector>

namespace algorithms {

/**
 * The route as a list of vertex.
 */
using Route = std::vector<std::size_t>;

/**
 * The basic class of graph router.
 */
class Router {
public:
    virtual ~Router() = default;

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

    /**
     * Traverse given graph and find all possible routes from given vertex.
     *
     * @param graph - The graph to traverse
     * @param s - The start vertex
     */
    virtual void
    calculate(const Graph& graph, std::size_t s)
        = 0;

protected:
    void
    init(const Graph& graph, std::size_t s);

protected:
    std::vector<bool> marked;
    std::vector<std::size_t> edgeTo;
};

} // namespace algorithms
