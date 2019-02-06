#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <initializer_list>

#include <LinkedList.hpp>

#include "Point.hpp"

namespace algorithms {



/**
 *
 */
using Points = std::vector<Point>;



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
