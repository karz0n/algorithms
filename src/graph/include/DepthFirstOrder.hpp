#pragma once

#include "Types.hpp"
#include "DirectedGraph.hpp"

namespace algorithms {

/**
 * Depth first order sorter implementation
 */
class DepthFirstOrder {
public:
    explicit DepthFirstOrder(const DirectedGraph& graph, bool inTopologicalOrder = false);

    [[nodiscard]] const Vertices&
    reversePost() const;

private:
    void
    sort(const DirectedGraph& graph, bool inTopologicalOrder);

    void
    sort(const DirectedGraph& graph, std::size_t s, Marks& marks);

private:
    Vertices _reversePost;
};

} // namespace algorithms
