#include "Graph.hpp"

namespace algorithms {

Graph::Graph()
{
}

Graph::Graph(std::size_t vertices)
    : _edges{0}
    , _vertices{vertices}
{
}

void
Graph::connect(std::size_t v1, std::size_t v2)
{
    _edges++;
    _vertices[v1].push_front(v2);
    _vertices[v2].push_front(v1);
}

const Graph::Adjacency
Graph::adjacency(std::size_t v) const
{
    return _vertices[v];
}

std::size_t
Graph::vertices() const
{
    return _vertices.size();
}

std::size_t
Graph::edges() const
{
    return _edges;
}

void
Graph::reset(std::size_t vertices)
{
    _edges = 0;
    Vertices(vertices).swap(_vertices);
}

} // namespace algorithms
