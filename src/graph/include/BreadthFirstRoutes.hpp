#pragma once

#include "Routes.hpp"

namespace algorithms {

/**
 * BFS algorithm graph implementation.
 *
 * Properties:
 *  - computes shortest path from s to t (fewest number of edges)
 *  - each vertex connected to s is visited once
 *  - finds vertices connected to s in constant time
 *  - finds a path to s in time proportional to its length
 *
 *  Not optimal in finding best path between two vertices.
 */
class BreadthFirstRoutes final : public Routes {
public:
    BreadthFirstRoutes(const Graph& graph, std::size_t s);

private:
    void
    traverse(const Graph& graph, std::size_t s);
};

} // namespace algorithms
