#include "DepthFirstOrder.hpp"

#include "DirectedCycleFinder.hpp"

#include <stdexcept>

namespace algorithms {

DepthFirstOrder::DepthFirstOrder(const Digraph& graph, bool inTopologicalOrder /*= false*/)
{
    sort(graph, inTopologicalOrder);
}

const Vertices&
DepthFirstOrder::reversePost() const&
{
    return _reversePost;
}

Vertices&&
DepthFirstOrder::reversePost() &&
{
    return std::move(_reversePost);
}

void
DepthFirstOrder::sort(const Digraph& graph, bool inTopologicalOrder)
{
    if (inTopologicalOrder) {
        DirectedCycleFinder finder{graph};
        if (finder.hasCycle()) {
            throw std::logic_error{"Directed cycle in graph detected"};
        }
    }

    Marks visitMarks(graph.verticesCount(), false);
    for (std::size_t s = 0; s < graph.verticesCount(); ++s) {
        if (!visitMarks[s]) {
            sort(graph, s, visitMarks);
        }
    }
}

void
DepthFirstOrder::sort(const Digraph& graph, std::size_t s, Marks& visitMarks)
{
    visitMarks[s] = true;

    for (const std::size_t v : graph.adjacency(s)) {
        if (!visitMarks[v]) {
            sort(graph, v, visitMarks);
        }
    }

    // Push out vertex to topological sorted list of vertices
    _reversePost.push_back(s);
}

} // namespace algorithms
