#pragma once

#include "FlowEdge.hpp"

#include <forward_list>
#include <vector>

namespace algorithms {

class FlowNetwork {
public:
    using EdgesList = std::forward_list<FlowEdge>;
    using Forest = std::vector<EdgesList>;

    FlowNetwork() = default;

    explicit FlowNetwork(std::size_t numberOfVertices);

    void
    add(const FlowEdge& edge);

    [[nodiscard]] const EdgesList&
    adjacency(std::size_t v) const;

    [[nodiscard]] EdgesList&
    adjacency(std::size_t v);

    [[nodiscard]] std::size_t
    verticesCount() const;

    void
    reset(std::size_t numberOfVertices);

    [[nodiscard]] bool
    empty() const;

private:
    Forest _forest;
};

} // namespace algorithms
