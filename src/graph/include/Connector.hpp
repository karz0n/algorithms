#pragma once

#include "Graph.hpp"

namespace algorithms {

/**
 * Connector algorithm for graph implementation.
 */
class Connector {
public:
    explicit Connector(const Graph& graph);

    /**
     * Checks if two vertex are connected on constant time.
     *
     * @param v The vertex one
     * @param w The vertex two
     *
     * @return @c true two vertex are connected, @c false otherwise.
     */
    [[nodiscard]] bool
    connected(std::size_t v, std::size_t w) const;

    /**
     * Returns total number of components (groups of connected to each other vertex).
     *
     * @return The total number of components.
     */
    [[nodiscard]] std::size_t
    count() const;

    /**
     * Returns the component of given vertex.
     *
     * @param v The vertex.
     *
     * @return The component's id of given vertex.
     */
    [[nodiscard]] std::size_t
    id(std::size_t v) const;

private:
    void
    process(const Graph& graph);

    void
    traverse(const Graph& graph, std::size_t s, std::size_t c);

private:
    std::size_t _count;
    std::vector<bool> _marked;
    std::vector<std::size_t> _compTo;
};

} // namespace algorithms
