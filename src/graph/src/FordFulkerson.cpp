#include "FordFulkerson.hpp"

#include <queue>
#include <optional>
#include <functional>

namespace algorithms {

using EdgeRef = std::reference_wrapper<FlowEdge>;
using EdgeOrNull = std::optional<EdgeRef>;
using Edges = std::vector<EdgeOrNull>;

static bool
hasAugmentingPath(FlowNetwork& network, std::size_t s, std::size_t t, Edges& edges, Marks& marks)
{
    std::queue<std::size_t> vs;
    vs.push(s);
    marks[s] = true;

    /* Find path from s to t by BFS algorithm */
    while (!vs.empty() && !marks[t]) {
        const std::size_t v{vs.front()};
        vs.pop();

        /* Consider only not full (forward) and not empty (backward) edges */
        for (auto& edge : network.adjacency(v)) {
            const std::size_t w{edge.other(v)};
            if (edge.residualCapacityTo(w) > 0 && !marks[w]) {
                edges[w] = std::make_optional<EdgeRef>(edge);
                marks[w] = true;
                vs.push(w);
            }
        }
    }

    return marks[t];
}

FordFulkerson::FordFulkerson(const FlowNetwork& network, std::size_t s, std::size_t t)
    : _value{0.0}
{
    traverse(network, s, t);
}

double
FordFulkerson::value() const
{
    return _value;
}

const Vertices&
FordFulkerson::minCut() const
{
    return _minCut;
}

void
FordFulkerson::traverse(FlowNetwork network, std::size_t s, std::size_t t)
{
    Edges edges(network.verticesCount());
    Marks marks(network.verticesCount());

    while (hasAugmentingPath(network, s, t, edges, marks)) {
        // Find bottleneck capacity
        double bottle{std::numeric_limits<double>::max()};
        for (std::size_t v = t; v != s; v = edges[v]->get().other(v)) {
            bottle = std::min(bottle, edges[v]->get().residualCapacityTo(v));
        }

        // Augment flow by bottleneck capacity
        for (std::size_t v = t; v != s; v = edges[v]->get().other(v)) {
            edges[v]->get().addResidualFlowTo(v, bottle);
        }

        _value += bottle;

        Edges(network.verticesCount()).swap(edges);
        Marks(network.verticesCount()).swap(marks);
    };

    /* Construct min-cut from vertices which are present at the end */
    for (std::size_t v = 0; v < network.verticesCount(); ++v) {
        if (marks[v]) {
            _minCut.push_back(v);
        }
    }
}

} // namespace algorithms
