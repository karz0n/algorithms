#include "FlowNetwork.hpp"

namespace algorithms {

FlowNetwork::FlowNetwork(std::size_t numberOfVertices)
    : _forest(numberOfVertices)
{
}

void
FlowNetwork::add(const FlowEdge& edge)
{
    const std::size_t v{edge.from()};
    const std::size_t w{edge.to()};
    _forest[v].push_front(edge); // Forward edge
    _forest[w].push_front(edge); // Backward edge
}

const FlowNetwork::EdgesList&
FlowNetwork::adjacency(std::size_t v) const
{
    return _forest[v];
}

FlowNetwork::EdgesList&
FlowNetwork::adjacency(std::size_t v)
{
    return _forest[v];
}

std::size_t
FlowNetwork::verticesCount() const
{
    return _forest.size();
}

void
FlowNetwork::reset(std::size_t numberOfVertices)
{
    Forest(numberOfVertices).swap(_forest);
}

bool
FlowNetwork::empty() const
{
    return _forest.empty();
}

} // namespace algorithms
