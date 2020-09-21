#pragma once

#include "Types.hpp"
#include "Graph.hpp"

namespace algorithms {

/**
 * The class of directed graph.
 */
class DirectedGraph final : public Graph {
public:
    DirectedGraph() = default;

    explicit DirectedGraph(std::size_t numberOfVertices);

    void
    connect(std::size_t v1, std::size_t v2) override;

    [[nodiscard]] DirectedGraph
    reverse() const;

    [[nodiscard]] static bool
    hasCycle(const DirectedGraph& graph);

    [[nodiscard]] static bool
    hasCycle(const DirectedGraph& graph, std::size_t s);

public:
    /**
     * Counts the number of loops in graph.
     * @param graph The given loop.
     * @return The number of loops.
     */
    [[nodiscard]] static std::size_t
    countOfSelfLoop(const Graph& graph);

    /**
     * Calculates the average number of degree in provided graph.
     * @param graph The given graph.
     * @return The average degree.
     */
    [[nodiscard]] static double
    averageDegree(const Graph& graph);
};

} // namespace algorithms
