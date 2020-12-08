#pragma once

#include "DirectedEdge.hpp"

#include <vector>
#include <forward_list>

namespace algorithms {

/**
 * Directed edge weighted graph representation
 *
 * Note: Allows self-loops and parallel edges
 */
class EdgeWeightedDigraph {
public:
    using DirectedEdgesList = std::forward_list<DirectedEdge>;
    using Forest = std::vector<DirectedEdgesList>;

    /**
     * Init empty graph.
     */
    EdgeWeightedDigraph();

    /**
     * Init graph with given number of vertices.
     * @param numberOfVertices The number of vertices.
     */
    explicit EdgeWeightedDigraph(std::size_t numberOfVertices);

    /**
     * Add edge to the graph.
     * @param edge The edge to add
     */
    void
    add(const DirectedEdge& edge);

    /**
     * Returns vertices which are adjacent to given vertex.
     * @param v The target vertex.
     * @return The list of adjacent vertices.
     */
    [[nodiscard]] const DirectedEdgesList&
    adjacency(std::size_t v) const;

    /**
     * Returns all edges
     * @return The list of all edges
     */
    [[nodiscard]] DirectedEdges
    edges() const;

    /**
     * Returns total number of vertices.
     * @return The number of vertices.
     */
    [[nodiscard]] std::size_t
    verticesCount() const;

    /**
     * Returns total number of edges.
     * @return The number of edges.
     */
    [[nodiscard]] std::size_t
    edgesCount() const;

    /**
     * Re-init graph using given number of vertices.
     * @param numberOfVertices The number of vertices
     */
    void
    reset(std::size_t numberOfVertices);

    /**
     * Returns status of emptiness of graph.
     * @return @c true iff graph is empty, @c false otherwise
     */
    [[nodiscard]] bool
    empty() const;

private:
    std::size_t _edges;
    Forest _forest;
};

} // namespace algorithms
