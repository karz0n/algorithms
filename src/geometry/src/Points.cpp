#include "Points.hpp"

#include <cmath>

namespace algorithms {

float
getDistance(const Point& p1, const Point& p2)
{
    return std::sqrt(std::pow(p2.x - p1.x, 2.f) + std::pow(p2.y - p1.y, 2.f));
}

int
getOrientation(const Point& p1, const Point& p2, const Point& p3)
{
    float v = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    return (v == 0.f) ? 0 : (v > 0.f) ? 1 : 2;
}

} // namespace algorithms
