#include "Graph.hpp"

namespace algorithms {

Graph::Graph()
    : edges{0}
{
}

Graph::Graph(std::size_t numberOfVertices)
    : edges{0}
    , vertices{numberOfVertices}
{
}

Graph::Adjacency
Graph::adjacency(std::size_t v) const
{
    return vertices[v];
}

std::size_t
Graph::verticesCount() const
{
    return vertices.size();
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
    Vertices(numberOfVertices).swap(vertices);
}

} // namespace algorithms
