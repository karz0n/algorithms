#include "Digraph.hpp"

namespace algorithms {

Digraph::Digraph(std::size_t numberOfVertices)
    : Graph{numberOfVertices}
{
}

void
Digraph::connect(std::size_t v1, std::size_t v2)
{
    edges++;
    forest[v1].push_front(v2);
}

Digraph
Digraph::reverse() const
{
    const std::size_t count = verticesCount();
    Digraph output{count};
    for (std::size_t s = 0; s < count; ++s) {
        for (const std::size_t v : forest[s]) {
            output.connect(v, s);
        }
    }
    return output;
}

std::size_t
Digraph::countOfSelfLoop(const Graph& graph)
{
    std::size_t count{0};
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        for (std::size_t w : graph.adjacency(v)) {
            if (v == w) {
                count++;
            }
        }
    }
    return count;
}

double
Digraph::averageDegree(const Graph& graph)
{
    double sum{0};
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        sum += Graph::degree(graph, v);
    }
    return sum / graph.verticesCount();
}

} // namespace algorithms
