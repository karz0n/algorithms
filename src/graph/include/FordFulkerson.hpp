#pragma once

#include "Types.hpp"
#include "FlowNetwork.hpp"

namespace algorithms {

/**
 * Finds max-flow and min-cut of the flow network
 */
class FordFulkerson {
public:
    FordFulkerson(const FlowNetwork& network, std::size_t s, std::size_t t);

    [[nodiscard]] double
    value() const;

    [[nodiscard]] const Vertices&
    minCut() const;

private:
    void
    traverse(FlowNetwork network, std::size_t s, std::size_t t);

private:
    double _value;
    Vertices _minCut;
};

} // namespace algorithms
