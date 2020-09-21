#pragma once

#include "Types.hpp"
#include "Graph.hpp"

namespace algorithms {

/**
 * Component spreader algorithms implementation.
 *
 * Properties:
 *  - divides graph into connected components
 *  - each vertex is visited only once
 *  - detects connection between vertices in constant time
 */
class ComponentSpreader {
public:
    explicit ComponentSpreader(const Graph& graph);

    /**
     * Checks if two vertex are connected (constant time).
     *
     * @param v The vertex one
     * @param w The vertex two
     *
     * @return @c true iff two vertex are connected, @c false otherwise.
     */
    [[nodiscard]] bool
    connected(std::size_t v, std::size_t w) const;

    /**
     * Returns the total number of components (groups of connected to each other vertex).
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
    traverse(const Graph& graph);

    void
    traverse(const Graph& graph, std::size_t s, std::size_t component, Marks& marks);

private:
    std::size_t _count;
    std::vector<std::size_t> _components;
};

} // namespace algorithms
