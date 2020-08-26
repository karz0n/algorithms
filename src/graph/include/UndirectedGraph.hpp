#pragma once

#include "Graph.hpp"

namespace algorithms {

/**
 * The class of undirected graph.
 */
class UndirectedGraph : public Graph {
public:
    UndirectedGraph() = default;

    explicit UndirectedGraph(std::size_t numberOfVertices);

    void
    connect(std::size_t v1, std::size_t v2) override;
};

} // namespace algorithms
