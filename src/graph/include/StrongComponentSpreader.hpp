#pragma once

#include "Types.hpp"
#include "DirectedGraph.hpp"

namespace algorithms {

/**
 * Strong component spreader algorithms implementation.
 *
 * Vertices v and w are strong connected if there is a directed path from v to w and vice versa.
 * Therefore strong connected component consist of vertices which have strong connection between
 * themselves.
 *
 * Properties:
 *  - divides graph into strong connected components
 *  - detects connection between vertices in constant time
 */
class StrongComponentSpreader {
public:
    explicit StrongComponentSpreader(const DirectedGraph& graph);

    [[nodiscard]] bool
    connected(std::size_t v, std::size_t w) const;

    [[nodiscard]] std::size_t
    count() const;

    [[nodiscard]] std::size_t
    id(std::size_t v) const;

private:
    void
    traverse(const DirectedGraph& graph);

    void
    traverse(const DirectedGraph& graph, std::size_t s, std::size_t component, Marks& marks);

private:
    std::size_t _count;
    std::vector<std::size_t> _components;
};

} // namespace algorithms
