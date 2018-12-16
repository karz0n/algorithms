#include "Comparators.hpp"

namespace algorithms {

int ccw(const Point& a, const Point& b, const Point& c)
{
    double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area < 0) return -1;
    if (area > 0) return +1;
    return 0;
}

//------------------------------------------------------------------------------------------

PolarOrder::PolarOrder(const Point& base)
    : _base{base}
{ }

int PolarOrder::compare(const Point& p1, const Point& p2) const
{
    double dy1 = p1.y - _base.y;
    double dy2 = p2.y - _base.y;

    if (dy1 == 0.0 && dy2 == 0.0) {

    }
    else if (dy1 >= 0 && dy2 < 0) {
        return -1;
    }
    else if (dy2 >= 0 && dy1 < 0) {
        return +1;
    }
    else {
        return -ccw(_base, p1, p2);
    }

    return 0;
}

//------------------------------------------------------------------------------------------

PolarOrder Comparators::byPolarOrder(const Point& base)
{
    return PolarOrder{base};
}

} // namespace algorithms
