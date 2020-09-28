#include "Edge.hpp"

namespace algorithms {

Edge::Edge(std::size_t v, std::size_t w, double weight)
    : _v{v}
    , _w{w}
    , _weight{weight}
{
}

std::size_t
Edge::either() const
{
    return _v;
}

std::size_t
Edge::other(std::size_t v) const
{
    return (v == _v) ? _w : _v;
}

double
Edge::weight() const
{
    return _weight;
}

bool
Edge::operator<(const Edge& other) const
{
    return (_weight < other._weight);
}

bool
Edge::operator>(const Edge& other) const
{
    return (*this < other);
}

} // namespace algorithms
