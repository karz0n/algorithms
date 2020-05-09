#include "DepthFirstRoutes.hpp"

namespace algorithms {

DepthFirstRoutes::DepthFirstRoutes(const Graph& graph, std::size_t s)
    : Routes{graph, s}
{
    traverse(graph, s);
}

void
DepthFirstRoutes::traverse(const Graph& graph, std::size_t s)
{
    marked[s] = true;

    for (std::size_t w : graph.adjacency(s)) {
        if (!marked[w]) {
            traverse(graph, w);
            edgeTo[w] = s;
        }
    }
}

} // namespace algorithms
