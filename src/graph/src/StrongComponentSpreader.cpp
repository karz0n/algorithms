#include "StrongComponentSpreader.hpp"
#include "DepthFirstOrder.hpp"

#include <limits>

namespace algorithms {

StrongComponentSpreader::StrongComponentSpreader(const DirectedGraph& graph)
    : _count{0}
    , _components(graph.verticesCount(), std::numeric_limits<std::size_t>::max())
{
    traverse(graph);
}

bool
StrongComponentSpreader::connected(std::size_t v, std::size_t w) const
{
    if (v == w) {
        return true;
    }
    return (_components[v] == _components[w]);
}

std::size_t
StrongComponentSpreader::count() const
{
    return _count;
}

std::size_t
StrongComponentSpreader::id(std::size_t v) const
{
    return _components[v];
}

void
StrongComponentSpreader::traverse(const DirectedGraph& graph)
{
    if (graph.empty()) {
        return;
    }

    DepthFirstOrder order{graph.reverse()};
    const auto& vertices = order.reversePost();

    Marks marks(vertices.size(), false);
    for (auto it = vertices.crbegin(); it != vertices.crend(); ++it) {
        const std::size_t v = *it;
        if (!marks[v]) {
            traverse(graph, v, _count++, marks);
        }
    }
}

void
StrongComponentSpreader::traverse(const DirectedGraph& graph, std::size_t s, std::size_t component,
                                  Marks& marks)
{
    _components[s] = component;

    marks[s] = true;
    for (const std::size_t v : graph.adjacency(s)) {
        if (!marks[v]) {
            traverse(graph, v, component, marks);
        }
    }
}

} // namespace algorithms
