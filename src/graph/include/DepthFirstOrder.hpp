#pragma once

#include "Types.hpp"
#include "Digraph.hpp"
#include "EdgeWeightedDigraph.hpp"

namespace algorithms {

/**
 * Depth first order sorter implementation
 */
class DepthFirstOrder {
public:
    explicit DepthFirstOrder(const Digraph& graph, bool inTopologicalOrder = false);

    explicit DepthFirstOrder(const EdgeWeightedDigraph& graph, bool inTopologicalOrder = false);

    /**
     * Returns the vertices in pre-order
     * @return the vertices in pre-order
     */
    [[nodiscard]] const Vertices&
    pre() const;

    /**
     * Returns the pre-order number of given vertex
     * @param v the given vertex
     * @return the pre-order number of vertex
     */
    [[nodiscard]] std::size_t
    pre(std::size_t v) const;

    /**
     * Returns the vertices in post-order
     * @return the vertices in post-order
     */
    [[nodiscard]] const Vertices&
    post() const;

    /**
     * Returns the post-order number of given vertex
     * @param v the given vertex
     * @return the post-order number of vertex
     */
    [[nodiscard]] std::size_t
    post(std::size_t v) const;

    /**
     * Returns vertices in reverse post-order
     * @return vertices in reverse post-order
     */
    [[nodiscard]] Vertices
    reversePost() const;

private:
    template<typename GraphType>
    void
    sort(const GraphType& graph, bool inTopologicalOrder);

    template<typename GraphType>
    void
    sort(const GraphType& graph,
         std::size_t v,
         Marks& visitMarks,
         std::size_t& preCounter,
         std::size_t& postCounter);

private:
    Vertices _pre;
    Vertices _preOrder;
    Vertices _post;
    Vertices _postOrder;
};

} // namespace algorithms
