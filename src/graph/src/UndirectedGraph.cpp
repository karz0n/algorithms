#include "UndirectedGraph.hpp"

namespace algorithms {

UndirectedGraph::UndirectedGraph(std::size_t numberOfVertices)
    : Graph{numberOfVertices}
{
}

void
UndirectedGraph::connect(std::size_t v1, std::size_t v2)
{
    edges++;
    forest[v1].push_front(v2);
    forest[v2].push_front(v1);
}

std::size_t
UndirectedGraph::countOfSelfLoop(const Graph& graph)
{
    std::size_t count{0};
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        for (std::size_t w : graph.adjacency(v)) {
            if (v == w) {
                count++;
            }
        }
    }
    return count / 2;
}

double
UndirectedGraph::averageDegree(const Graph& graph)
{
    return 2.0 * graph.edgesCount() / graph.verticesCount();
}

} // namespace algorithms
