#pragma once

#include "EdgeWeightedGraph.hpp"

namespace algorithms {

/**
 * Kruskal greedy algorithms implementation
 */
class KruskalMinSpanningTree {
public:
    using Edges = std::vector<Edge>;

    explicit KruskalMinSpanningTree(const EdgeWeightedGraph& graph);

    [[nodiscard]] const Edges&
    edges() const;

    [[nodiscard]] double
    weight() const;

private:
    void
    traverse(const EdgeWeightedGraph& graph);

private:
    double _weight;
    Edges _edges;
};

} // namespace algorithms
