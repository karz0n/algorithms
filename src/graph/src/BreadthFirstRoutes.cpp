#include <BreadthFirstRoutes.hpp>

#include <queue>

namespace algorithms {

BreadthFirstRoutes::BreadthFirstRoutes(const Graph& graph, std::size_t s)
    : Routes{graph, s}
{
    traverse(graph, s);
}

void
BreadthFirstRoutes::traverse(const Graph& graph, std::size_t s)
{
    if (graph.empty()) {
        return;
    }

    std::queue<std::size_t> vs;
    vs.push(s);
    while (!vs.empty()) {
        s = vs.front();
        vs.pop();

        /* Examine all adjacency in order of increasing distance from s */
        for (const std::size_t v : graph.adjacency(s)) {
            if (!marks[v]) {
                source[v] = s;
                marks[v] = true;
                vs.push(v);
            }
        }
    }
}

} // namespace algorithms
