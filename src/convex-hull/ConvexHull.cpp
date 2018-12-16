#include "ConvexHull.hpp"

#include <stack>

namespace algorithms {

ConvexHull::ConvexHull(const Points& points)
{
    search(points);
}

void ConvexHull::search(const Points& points)
{
    Points target{points};

    sortByOrder(target);
    sortRelativeTo(target);

    std::stack<Point> hull;
    hull.push(target[0]);
    hull.push(target[1]);

    for (std::size_t i = 2; i < target.size(); ++i) {
        Point top = hull.top();
        hull.pop();
        while (ccw(hull.top(), top, target[i]) <= 0) {
            top = hull.top();
            hull.pop();
        }
        hull.push(top);
        hull.push(target[i]);
    }
}

const Points& ConvexHull::get() const
{
    return _hull;
}

void ConvexHull::sortByOrder(Points&)
{

}

void ConvexHull::sortRelativeTo(Points&)
{

}

} // namespace algorithms
