#include "Digraph.hpp"

namespace algorithms {

static bool
hasCycle(const Digraph& graph, std::size_t s, Marks& marks, Marks& state)
{
    marks[s] = true;
    state[s] = true; // Mark current vertex in recursion tree
    for (const std::size_t v : graph.adjacency(s)) {
        if (state[v]) {
            // Adjacent vertex has already present in recursion tree
            return true;
        }
        if (!marks[v]) {
            // Move deeper and check all descendants
            if (hasCycle(graph, v, marks, state)) {
                return true;
            }
        }
    }
    state[s] = false; // Unmark current vertex in recursion tree
    return false;
}

Digraph::Digraph(std::size_t numberOfVertices)
    : Graph{numberOfVertices}
{
}

void
Digraph::connect(std::size_t v1, std::size_t v2)
{
    edges++;
    forest[v1].push_front(v2);
}

Digraph
Digraph::reverse() const
{
    const std::size_t count = verticesCount();
    Digraph output{count};
    for (std::size_t s = 0; s < count; ++s) {
        for (const std::size_t v : forest[s]) {
            output.connect(v, s);
        }
    }
    return output;
}

bool
Digraph::hasCycle(const Digraph& graph)
{
    const std::size_t count = graph.verticesCount();
    if (count == 0) {
        return false;
    }

    Marks marks(count, false);
    Marks state(count, false);
    for (std::size_t s = 0; s < count; ++s) {
        if (!marks[s]) {
            if (algorithms::hasCycle(graph, s, marks, state)) {
                return true;
            }
        }
    }
    return false;
}

bool
Digraph::hasCycle(const Digraph& graph, std::size_t s)
{
    Marks marks(graph.verticesCount(), false);
    Marks state(graph.verticesCount(), false);
    return algorithms::hasCycle(graph, s, marks, state);
}

std::size_t
Digraph::countOfSelfLoop(const Graph& graph)
{
    std::size_t count{0};
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        for (std::size_t w : graph.adjacency(v)) {
            if (v == w) {
                count++;
            }
        }
    }
    return count;
}

double
Digraph::averageDegree(const Graph& graph)
{
    double sum{0};
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        sum += Graph::degree(graph, v);
    }
    return sum / graph.verticesCount();
}

} // namespace algorithms
