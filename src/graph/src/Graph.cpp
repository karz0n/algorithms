#include "Graph.hpp"

namespace algorithms {

Graph::Graph()
    : edges{0}
{
}

Graph::Graph(std::size_t numberOfVertices)
    : edges{0}
    , forest{numberOfVertices}
{
}

const Graph::Adjacency&
Graph::adjacency(std::size_t v) const
{
    return forest[v];
}

std::size_t
Graph::verticesCount() const
{
    return forest.size();
}

std::size_t
Graph::edgesCount() const
{
    return edges;
}

void
Graph::reset(std::size_t numberOfVertices)
{
    edges = 0;
    Forest(numberOfVertices).swap(forest);
}

std::size_t
Graph::degree(const Graph& graph, std::size_t s)
{
    const auto& adjacency = graph.adjacency(s);
    return std::distance(adjacency.cbegin(), adjacency.cend());
}

std::size_t
Graph::maxDegree(const Graph& graph)
{
    std::size_t max{0};
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        std::size_t degree = Graph::degree(graph, v);
        if (max < degree) {
            max = degree;
        }
    }
    return max;
}

bool
Graph::empty() const
{
    return forest.empty();
}

} // namespace algorithms
