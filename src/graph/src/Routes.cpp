#include "Routes.hpp"

#include <limits>

namespace algorithms {

bool
Routes::hasRouteTo(std::size_t vertex) const
{
    return marked[vertex];
}

Vertices
Routes::reachability() const
{
    Vertices output;
    for (std::size_t v{0}; v < marked.size(); ++v) {
        if (marked[v]) {
            output.push_back(v);
        }
    }
    return output;
}

Route
Routes::routeTo(std::size_t vertex) const
{
    if (!hasRouteTo(vertex)) {
        return Route{};
    }

    Route steps;
    steps.push_back(vertex);

    int p = edgeTo[vertex];
    while (p != -1) {
        steps.push_back(p);
        p = edgeTo[p];
    }

    /** Flip over our steps */
    return Route(steps.crbegin(), steps.crend());
}

Routes::Routes(const Graph& graph)
    : marked(graph.verticesCount(), false)
    , edgeTo(graph.verticesCount(), -1)
{
}

} // namespace algorithms
