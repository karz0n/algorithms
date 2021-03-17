#include "DepthFirstRoutes.hpp"

namespace algorithms {

DepthFirstRoutes::DepthFirstRoutes(const Graph& graph, std::size_t source)
    : Routes{graph}
{
    traverse(graph, source);
}

DepthFirstRoutes::DepthFirstRoutes(const Graph& graph, const Vertices& sources)
    : Routes{graph}
{
    for (std::size_t v : sources) {
        traverse(graph, v);
    }
}

void
DepthFirstRoutes::traverse(const Graph& graph, std::size_t source)
{
    marked[source] = true;
    for (std::size_t v : graph.adjacency(source)) {
        if (!marked[v]) {
            edgeTo[v] = source;
            /* Used recursion to go deeply of graph */
            traverse(graph, v);
        }
    }
}

} // namespace algorithms
