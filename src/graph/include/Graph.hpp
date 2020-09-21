#pragma once

#include <vector>
#include <forward_list>

namespace algorithms {

/**
 * The base graph class.
 *
 * @see UndirectedGraph
 * @see DirectedGraph
 */
class Graph {
public:
    using Adjacency = std::forward_list<std::size_t>;
    using Forest = std::vector<Adjacency>;

    /**
     * Init empty graph.
     */
    Graph();

    /**
     * Init graph with given number of vertices.
     * @param numberOfVertices The number of vertices.
     */
    explicit Graph(std::size_t numberOfVertices);

    /**
     * Connect two vertices.
     * @see DirectedGraph
     * @see UndirectedGraph
     * @param v1 The vertex number one
     * @param v2 The vertex number two
     */
    virtual void
    connect(std::size_t v1, std::size_t v2)
        = 0;

    /**
     * Returns vertices which are adjacent to given vertex.
     * @param v The target vertex.
     * @return The list of adjacent vertices.
     */
    [[nodiscard]] const Adjacency&
    adjacency(std::size_t v) const;

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

public:
    /**
     * Calculates degree of given vertex in graph.
     * @param graph The given graph.
     * @param s The given vertex.
     * @return The degree.
     */
    [[nodiscard]] static std::size_t
    degree(const Graph& graph, std::size_t s);

    /**
     * Calculates the max degree in provided graph.
     * @param graph The given graph.
     * @return The max degree.
     */
    [[nodiscard]] static std::size_t
    maxDegree(const Graph& graph);

protected:
    std::size_t edges;
    Forest forest;
};

} // namespace algorithms
