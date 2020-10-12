#pragma once

#include <vector>
#include <string>

namespace algorithms {

/**
 * The weighted edge representation
 */
class Edge {
public:
    Edge(std::size_t v, std::size_t w, double weight);

    [[nodiscard]] std::size_t
    either() const;

    [[nodiscard]] std::size_t
    other(std::size_t v) const;

    [[nodiscard]] double
    weight() const;

    [[nodiscard]] std::string
    toString() const;

    bool
    operator<(const Edge& other) const;

    bool
    operator>(const Edge& other) const;

    bool
    operator==(const Edge& other) const;

    bool
    operator!=(const Edge& other) const;

private:
    std::size_t _v;
    std::size_t _w;
    double _weight;
};

/** The list of weighted edges */
using Edges = std::vector<Edge>;

} // namespace algorithms
