#include "Routes.hpp"

#include <limits>

namespace algorithms {

bool
Routes::hasRouteTo(std::size_t v) const
{
    return marked[v];
}

Route
Routes::routeTo(std::size_t v) const
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

    /** Flip over steps */
    return Route(steps.crbegin(), steps.crend());
}

Routes::Routes(const Graph& graph, std::size_t s)
    : marked(graph.verticesCount(), false)
    , edgeTo(graph.verticesCount(), std::numeric_limits<std::size_t>::max())
{
    marked[s] = true;
    edgeTo[s] = s;
}

} // namespace algorithms
