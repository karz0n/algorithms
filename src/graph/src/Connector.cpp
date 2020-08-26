#include "Connector.hpp"

#include <limits>

namespace algorithms {

Connector::Connector(const Graph& graph)
    : _count{0}
    , _marked(graph.verticesCount(), false)
    , _compTo(graph.verticesCount(), std::numeric_limits<std::size_t>::max())
{
    process(graph);
}

bool
Connector::connected(std::size_t v, std::size_t w) const
{
    if (v == w) {
        return true;
    }
    return (_compTo[v] == _compTo[w]);
}

std::size_t
Connector::count() const
{
    return _count;
}

std::size_t
Connector::id(std::size_t v) const
{
    return _compTo[v];
}

void
Connector::process(const Graph& graph)
{
    _count = 0;
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        if (!_marked[v]) {
            traverse(graph, v, _count++);
        }
    }
}

void
Connector::traverse(const Graph& graph, std::size_t s, std::size_t c)
{
    _marked[s] = true;
    _compTo[s] = c;

    for (std::size_t w : graph.adjacency(s)) {
        if (!_marked[w]) {
            traverse(graph, w, c);
        }
    }
}

} // namespace algorithms
