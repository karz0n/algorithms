#pragma once

#include "Routes.hpp"

namespace algorithms {

/**
 * DFS algorithm graph implementation.
 *
 * Properties:
 *  - marks all vertices in time proportional to the sum of their degrees
 *  - each vertex connected to s is visited once
 *  - find vertices connected to s in constant time
 *  - find a path to s in time proportional to its length
 *
 *  Not optimal in finding best path between two vertices.
 */
class DepthFirstRoutes final : public Routes {
public:
    DepthFirstRoutes(const Graph& graph, std::size_t s);

private:
    void
    traverse(const Graph& graph, std::size_t s);
};

} // namespace algorithms
