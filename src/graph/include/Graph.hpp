#pragma once

#include <vector>
#include <forward_list>

namespace algorithms {

class Graph {
public:
    using Adjacency = std::forward_list<std::size_t>;
    using Vertices = std::vector<Adjacency>;

    Graph();

    Graph(std::size_t vertices);

    void
    connect(std::size_t v1, std::size_t v2);

    const Adjacency
    adjacency(std::size_t v) const;

    std::size_t
    vertices() const;

    std::size_t
    edges() const;

    void
    reset(std::size_t vertices);

private:
    std::size_t _edges;
    Vertices _vertices;
};

} // namespace algorithms
