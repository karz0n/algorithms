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
    float v = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return (v == 0.f) ? 0 : (v > 0.f) ? +1 : -1;
}

bool
CompareByX::operator()(const Point& p1, const Point& p2) const
{
    return (p1.x < p2.x);
}

bool
CompareByY::operator()(const Point& p1, const Point& p2) const
{
    return (p1.y < p2.y);
}

bool
CompareByXY::operator()(const Point& p1, const Point& p2) const
{
    if (p1.y < p2.y) {
        return true;
    }
    if (p1.y > p2.y) {
        return false;
    }
    if (p1.x < p2.x) {
        return true;
    }
    if (p1.x > p2.x) {
        return false;
    }
    return false;
}

CompareByPolarOrder::CompareByPolarOrder(const Point& base)
    : _base{base}
{
}

bool
CompareByPolarOrder::operator()(const Point& p1, const Point& p2) const
{
    const auto dx1 = p1.x - _base.x;
    const auto dy1 = p1.y - _base.y;
    const auto dx2 = p2.x - _base.x;
    const auto dy2 = p2.y - _base.y;

    if (dy1 >= 0 && dy2 < 0) { // p1 above, p2 below
        return true;
    }
    if (dy2 >= 0 && dy1 < 0) { // p1 below, p2 above
        return false;
    }
    if (dy1 == 0 && dy2 == 0) {
        // 3-collinear and horizontal
        if (dx1 >= 0 && dx2 < 0) {
            return true;
        }
        if (dx2 >= 0 && dx1 < 0) {
            return false;
        }
        return false;
    }

    // Both above or below
    return (getOrientation(_base, p1, p2) > 0);
}

} // namespace algorithms
