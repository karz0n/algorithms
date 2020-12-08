#pragma once

#include "Types.hpp"
#include "EdgeWeightedGraph.hpp"

namespace algorithms {

class PrimsMinSpanningTree {
public:
    explicit PrimsMinSpanningTree(const EdgeWeightedGraph& graph);

    [[nodiscard]] const Edges&
    edges() const;

    [[nodiscard]] double
    weight() const;

private:
    void
    traverse(const EdgeWeightedGraph& graph);

    void
    traverse(const EdgeWeightedGraph& graph, Marks& marks, std::size_t v);

private:
    double _weight;
    Edges _edges;
};

} // namespace algorithms