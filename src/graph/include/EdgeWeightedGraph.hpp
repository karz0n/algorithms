#pragma once

#include "Edge.hpp"

#include <vector>
#include <forward_list>

namespace algorithms {

/**
 * Edge weighted graph representation
 */
class EdgeWeightedGraph {
public:
    using EdgesList = std::forward_list<Edge>;
    using Forest = std::vector<EdgesList>;

    /**
     * Init empty graph.
     */
    EdgeWeightedGraph();

    /**
     * Init graph with given number of vertices.
     * @param numberOfVertices The number of vertices.
     */
    explicit EdgeWeightedGraph(std::size_t numberOfVertices);

    /**
     * Add edge to the graph.
     * @param edge The edge to add
     */
    void
    add(const Edge& edge);

    /**
     * Returns vertices which are adjacent to given vertex.
     * @param v The target vertex.
     * @return The list of adjacent vertices.
     */
    [[nodiscard]] const EdgesList&
    adjacency(std::size_t v) const;

    /**
     * Returns all edges
     * @return The list of all edges
     */
    [[nodiscard]] Edges
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
