#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <initializer_list>

#include <LinkedList.hpp>

namespace algorithms {

/**
 *
 */
struct Point {
    Point(double x, double y)
        : x{x}
        , y{y}
    { }

    double x;
    double y;
};

/**
 *
 */
using Points = std::vector<Point>;

/**
 *
 * @param a
 * @param b
 * @param c
 *
 * @return
 */
static int ccw(const Point& a, const Point& b, const Point& c)
{
    double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area < 0) return -1;
    if (area > 0) return +1;
    return 0;
}

/**
 *
 */
class ConvexHull {
public:
    ConvexHull() = default;

    ConvexHull(const Points& points);

    void search(const Points& points);

    const Points& get() const;

public:
    template <typename InputIt>
    static ConvexHull from(InputIt first, InputIt last)
    {
        return ConvexHull();
    }

    static ConvexHull from(std::initializer_list<Point> list)
    {
        return ConvexHull();
    }

private:
    void sortByOrder(Points& points);

    void sortRelativeTo(Points& points);

private:
    Points _hull;
};

} // namespace algorithms

#endif // CONVEXHULL_H
