#pragma once

#include "Types.hpp"
#include "Digraph.hpp"
#include "EdgeWeightedDigraph.hpp"

namespace algorithms {

/**
 * Directed cycle finder class.
 *
 * Finds directed cycle in directed graph and provide vertices those presented in it.
 */
class DirectedCycleFinder {
public:
    explicit DirectedCycleFinder(const Digraph& graph);

    explicit DirectedCycleFinder(const EdgeWeightedDigraph& graph);

    [[nodiscard]] bool
    hasCycle() const;

    [[nodiscard]] const Vertices&
    cycle() const;

private:
    template<typename GraphType>
    void
    traverse(const GraphType& graph);

    template<typename GraphType>
    void
    traverse(const GraphType& w,
             std::size_t s,
             Marks& visitMarks,
             Marks& stackMarks,
             Vertices& parentLinks);

    void
    makeCycleChain(const Vertices& parentLinks, std::size_t s, std::size_t w);

private:
    Vertices _cycle;
};

} // namespace algorithms