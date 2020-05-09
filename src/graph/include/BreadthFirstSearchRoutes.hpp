#pragma once

#include "Routes.hpp"

namespace algorithms {

/**
 * BFS algorithm for graph implementation
 */
class BreadthFirstSearchRoutes final : public Routes {
public:
    BreadthFirstSearchRoutes(const Graph& graph, std::size_t s);

private:
    void
    traverse(const Graph& graph, std::size_t s);
};

} // namespace algorithms
