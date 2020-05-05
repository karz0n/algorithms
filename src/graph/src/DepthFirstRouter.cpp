#include "DepthFirstRouter.hpp"

namespace algorithms {

void
DepthFirstRoutes::calculate(const Graph& graph, std::size_t s)
{
    init(graph, s);
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
