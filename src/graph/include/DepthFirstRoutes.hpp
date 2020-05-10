#pragma once

#include "Routes.hpp"

namespace algorithms {

/**
 * DFS algorithm graph implementation
 */
class DepthFirstRoutes final : public Routes {
public:
    DepthFirstRoutes(const Graph& graph, std::size_t s);

private:
    void
    traverse(const Graph& graph, std::size_t s);
};

} // namespace algorithms
