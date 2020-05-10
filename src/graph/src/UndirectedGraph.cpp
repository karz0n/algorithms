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
    vertices[v1].push_front(v2);
    vertices[v2].push_front(v1);
}

} // namespace algorithms
