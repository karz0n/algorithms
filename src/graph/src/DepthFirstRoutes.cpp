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
    marks[s] = true;
    for (std::size_t w : graph.adjacency(s)) {
        if (!marks[w]) {
            source[w] = s;
            /* Used recursion to go deeply of graph */
            traverse(graph, w);
        }
    }
}

} // namespace algorithms
