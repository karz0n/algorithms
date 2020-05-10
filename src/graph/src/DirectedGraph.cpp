#include "DirectedGraph.hpp"

namespace algorithms {

DirectedGraph::DirectedGraph(std::size_t numberOfVertices)
    : Graph{numberOfVertices}
{
}

void
DirectedGraph::connect(std::size_t v1, std::size_t v2)
{
    edges++;
    vertices[v1].push_front(v2);
}

} // namespace algorithms
