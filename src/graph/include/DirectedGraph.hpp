#pragma once

#include "Graph.hpp"

namespace algorithms {

/**
 * The class of directed graph.
 */
class DirectedGraph : public Graph {
public:
    DirectedGraph() = default;

    DirectedGraph(std::size_t numberOfVertices);

    void
    connect(std::size_t v1, std::size_t v2) override;
};

} // namespace algorithms
