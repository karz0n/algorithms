#include "Routes.hpp"

#include <limits>

namespace algorithms {

bool
Routes::hasRouteTo(std::size_t v) const
{
    return marks[v];
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
    std::size_t n = source[v]; // Get source vertex (where did we come from to reach this vertex)
    while (p != n) {
        steps.push_back(p = n);
        n = source[n];
    }

    /** Flip over steps */
    return Route(steps.crbegin(), steps.crend());
}

Routes::Routes(const Graph& graph, std::size_t s)
    : marks(graph.verticesCount(), false)
    , source(graph.verticesCount(), std::numeric_limits<std::size_t>::max())
{
    marks[s] = true;
    source[s] = s;
}

} // namespace algorithms
