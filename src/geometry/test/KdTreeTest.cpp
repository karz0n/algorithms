#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "KdTree.hpp"

using namespace algorithms;

Points
getPoints(std::size_t count, float from, float to)
{
    Points points(count);
    auto numbers = Sequence::numbers<float>(2 * count, from, to);
    while (count--) {
        points[count].x = numbers[count + 1];
        points[count].y = numbers[count];
    }
    return points;
}

Point
getPoint(float from, float to)
{
    auto numbers = Sequence::numbers(2, from, to);
    return Point{numbers[0], numbers[1]};
}

std::tuple<Point, float>
getClosestPointTo(const Point& queryPoint, const Points& points)
{
    Point bestPoint;
    float bestDistance = std::numeric_limits<float>::max();
    for (const auto& p : points) {
        float d = queryPoint.distanceTo(p);
        if (d < bestDistance) {
            bestDistance = d;
            bestPoint = p;
        }
    }
    return std::make_tuple(bestPoint, bestDistance);
}

TEST(KdTreeTest, NearestPoint)
{
    Points points = getPoints(100, 0.f, 100.f);

    auto queryPoint = getPoint(0.f, 100.f);
    auto [bestPoint1, bestDistance1] = getClosestPointTo(queryPoint, points);

    KdTree tree;
    tree.create(points);
    auto [bestPoint2, bestDistance2] = tree.nearestTo(queryPoint);

    EXPECT_EQ(bestPoint1, bestPoint2);
    EXPECT_FLOAT_EQ(bestDistance1, bestDistance2);
}
