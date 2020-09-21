#include "DepthFirstOrder.hpp"

#include <stdexcept>

namespace algorithms {

DepthFirstOrder::DepthFirstOrder(const DirectedGraph& graph, bool inTopologicalOrder /*= false*/)
{
    sort(graph, inTopologicalOrder);
}

const Vertices&
DepthFirstOrder::reversePost() const
{
    return _reversePost;
}

void
DepthFirstOrder::sort(const DirectedGraph& graph, bool inTopologicalOrder)
{
    Marks marks(graph.verticesCount(), false);
    for (std::size_t s = 0; s < graph.verticesCount(); ++s) {
        if (!marks[s]) {
            if (inTopologicalOrder && DirectedGraph::hasCycle(graph, s)) {
                throw std::logic_error{"Cycle in graph detected"};
            }
            sort(graph, s, marks);
        }
    }
}

void
DepthFirstOrder::sort(const DirectedGraph& graph, std::size_t s, Marks& marks)
{
    marks[s] = true;

    for (const std::size_t v : graph.adjacency(s)) {
        if (!marks[v]) {
            sort(graph, v, marks);
        }
    }

    // Push out vertex to topological sorted list of vertices
    _reversePost.push_back(s);
}

} // namespace algorithms
