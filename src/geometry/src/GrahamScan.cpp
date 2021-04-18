#include "GrahamScan.hpp"

#include <stack>

namespace algorithms {

GrahamScan::GrahamScan(const Points& points)
{
    scan(points);
}

void
GrahamScan::scan(Points points)
{
    static const std::size_t k0{0};

    // Sort points by XY coordinates
    std::sort(points.begin(), points.end(), CompareByXY{});

    // Sort points by polar order towards point with the smallest Y coordinate
    std::sort(std::next(points.begin()), points.end(), CompareByPolarOrder{points[k0]});

    // Get first not equal point
    std::size_t k1{1};
    for (; k1 < points.size(); ++k1) {
        if (points[k0] != points[k1]) {
            break;
        }
    }
    if (k1 == points.size()) {
        return;
    }

    // Get first not collinear with k0 and k1 points
    std::size_t k2{k1 + 1};
    for (; k2 < points.size(); ++k2) {
        if (getOrientation(points[k0], points[k1], points[k2]) != 0) {
            break;
        }
    }
    if (k2 == points.size()) {
        return;
    }

    std::stack<Point> hull;
    hull.push(points[k0]);     // Add 1st extreme point
    hull.push(points[k2 - 1]); // Add 2nd extreme point

    // Scan for other extreme points
    for (std::size_t i{k2}; i < points.size(); ++i) {
        Point top = hull.top();
        hull.pop();
        while (getOrientation(hull.top(), top, points[i]) <= 0) {
            top = hull.top();
            hull.pop();
        }
        hull.push(top);
        hull.push(points[i]);
    }

    // Compose extremes points
    _hull.clear();
    _hull.resize(hull.size());
    for (long n = static_cast<long>(hull.size() - 1); n >= 0; --n) {
        _hull[n] = hull.top();
        hull.pop();
    }
}

} // namespace algorithms