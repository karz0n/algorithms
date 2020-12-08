#pragma once

#include <vector>
#include <string>

namespace algorithms {

/**
 * The directed weighted edge representation
 */
class DirectedEdge {
public:
    DirectedEdge(std::size_t from, std::size_t to, double weight);

    [[nodiscard]] std::size_t
    from() const;

    [[nodiscard]] std::size_t
    to() const;

    [[nodiscard]] double
    weight() const;

    [[nodiscard]] std::string
    toString() const;

    bool
    operator<(const DirectedEdge& other) const;

    bool
    operator>(const DirectedEdge& other) const;

    bool
    operator==(const DirectedEdge& other) const;

    bool
    operator!=(const DirectedEdge& other) const;

private:
    std::size_t _from;
    std::size_t _to;
    double _weight;
};

/** The list of directed weighted edges */
using DirectedEdges = std::vector<DirectedEdge>;

} // namespace algorithms