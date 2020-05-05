#include "Router.hpp"

#include <limits>

namespace algorithms {

bool
Router::hasRouteTo(std::size_t v) const
{
    return marked[v];
}

Route
Router::routeTo(std::size_t v) const
{
    if (!hasRouteTo(v)) {
        return Route{};
    }

    Route steps;
    steps.push_back(v);

    std::size_t p = v;
    std::size_t n = edgeTo[v];
    while (p != n) {
        steps.push_back(p = n);
        n = edgeTo[n];
    }

    /** Reverse of steps */
    return Route(steps.crbegin(), steps.crend());
}

void
Router::init(const Graph& graph, std::size_t s)
{
    std::size_t count = graph.vertices();

    marked.resize(count, false);
    edgeTo.resize(count, std::numeric_limits<std::size_t>::max());

    marked[s] = true;
    edgeTo[s] = s;
}

} // namespace algorithms
