#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "KdTree.hpp"
#include "KdTreeEx.hpp"

using namespace algorithms;

static constexpr int POINTS_NUMBER = 100000;
static constexpr float POINTS_MIN_VALUE = 0.f;
static constexpr float POINTS_MAX_VALUE = 100000.f;

template<typename T>
class KdTreeTest : public ::testing::Test {
protected:
    void
    SetUp() override
    {
        _points = getPoints(POINTS_NUMBER, POINTS_MIN_VALUE, POINTS_MAX_VALUE);
    }

protected:
    Points _points;

protected:
    static Points
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

    static Point
    getPoint(float from, float to)
    {
        auto numbers = Sequence::numbers(2, from, to);
        return Point{numbers[0], numbers[1]};
    }

    static std::tuple<Point, float>
    getClosestPointTo(const Point& queryPoint, const Points& points)
    {
        Point bestPoint;
        float bestDistance = std::numeric_limits<float>::max();
        for (const auto& p : points) {
            float d = getDistance(queryPoint, p);
            if (d < bestDistance) {
                bestDistance = d;
                bestPoint = p;
            }
        }
        return std::make_tuple(bestPoint, bestDistance);
    }
};

using MyTypes = ::testing::Types<KdTree, KdTreeEx>;
TYPED_TEST_SUITE(KdTreeTest, MyTypes);

TYPED_TEST(KdTreeTest, NearestPoint)
{
    using Me = KdTreeTest<TypeParam>;

    auto queryPoint = Me::getPoint(POINTS_MIN_VALUE, POINTS_MAX_VALUE);
    auto [bestPoint1, bestDistance1] = Me::getClosestPointTo(queryPoint, Me::_points);

    TypeParam tree;
    tree.create(Me::_points);
    auto [bestPoint2, bestDistance2] = tree.nearestTo(queryPoint);

    EXPECT_EQ(bestPoint1, bestPoint2);
    EXPECT_FLOAT_EQ(bestDistance1, bestDistance2);
}
