#include "DirectedEdge.hpp"

#include <sstream>
#include <iomanip>

namespace algorithms {

DirectedEdge::DirectedEdge(std::size_t from, std::size_t to, double weight)
    : _from{from}
    , _to{to}
    , _weight{weight}
{
}

std::size_t
DirectedEdge::from() const
{
    return _from;
}

std::size_t
DirectedEdge::to() const
{
    return _to;
}

double
DirectedEdge::weight() const
{
    return _weight;
}

std::string
DirectedEdge::toString() const
{
    std::stringstream ss;
    ss << "{" << _from << ", " << _to << "} "
       << "[" << std::setprecision(5) << _weight << "]";
    return ss.str();
}

bool
DirectedEdge::operator<(const DirectedEdge& other) const
{
    return (_weight < other._weight);
}

bool
DirectedEdge::operator>(const DirectedEdge& other) const
{
    return !(*this < other);
}

bool
DirectedEdge::operator==(const DirectedEdge& other) const
{
    return (_from == other._from && _to == other._to);
}

bool
DirectedEdge::operator!=(const DirectedEdge& other) const
{
    return !(*this == other);
}

}