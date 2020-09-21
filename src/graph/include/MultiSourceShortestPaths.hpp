#pragma once

#include "Types.hpp"
#include "Graph.hpp"

#include <vector>

namespace algorithms {

class MultiSourceShortestPaths {
public:
    using Distances = std::vector<std::size_t>;

    MultiSourceShortestPaths(const Graph& graph, std::initializer_list<std::size_t> ss);

    [[nodiscard]] const Distances&
    distances() const;

private:
    void
    traverse(const Graph& graph, std::initializer_list<std::size_t> ss);

private:
    std::vector<std::size_t> _distances;
};

} // namespace algorithms