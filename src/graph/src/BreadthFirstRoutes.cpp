#include <BreadthFirstRoutes.hpp>

#include <queue>

namespace algorithms {

BreadthFirstRoutes::BreadthFirstRoutes(const Graph& graph, std::size_t source)
    : Routes{graph}
{
    traverse(graph, source);
}

BreadthFirstRoutes::BreadthFirstRoutes(const Graph& graph, const Vertices& sources)
    : Routes{graph}
{
    for (std::size_t v : sources) {
        traverse(graph, v);
    }
}

void
BreadthFirstRoutes::traverse(const Graph& graph, std::size_t source)
{
    if (graph.empty()) {
        return;
    }

    std::queue<std::size_t> vs;
    vs.push(source);
    while (!vs.empty()) {
        source = vs.front();
        vs.pop();

        marked[source] = true;

        /* Examine all adjacency in order of increasing distance from source */
        for (const std::size_t v : graph.adjacency(source)) {
            if (!marked[v]) {
                edgeTo[v] = source;
                marked[v] = true;
                vs.push(v);
            }
        }
    }
}

} // namespace algorithms
