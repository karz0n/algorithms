#pragma once

#include "Types.hpp"
#include "Digraph.hpp"

namespace algorithms {

/**
 * Directed cycle finder class.
 *
 * Finds directed cycle in directed graph and provide vertices those presented in it.
 */
class DirectedCycleFinder {
public:
    explicit DirectedCycleFinder(const Digraph& graph);

    [[nodiscard]] bool
    hasCycle() const;

    [[nodiscard]] const Vertices&
    cycle() const;

private:
    void
    traverse(const Digraph& graph);

    void
    traverse(const Digraph& graph,
             std::size_t s,
             Marks& visitMarks,
             Marks& stackMarks,
             Vertices& parentLinks);

private:
    Vertices _cycle;
};

} // namespace algorithms