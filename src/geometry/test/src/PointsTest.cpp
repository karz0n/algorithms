#include <gtest/gtest.h>

#include <Points.hpp>

using namespace algorithms;

TEST(PointsTest, GetOrientation)
{
    Point p1{0.0, 0.0}, p2{4.0, 4.0};

    EXPECT_EQ(getOrientation(p1, p2, Point{1.0, 1.0}), 0); // Expect: Colinear
    EXPECT_EQ(getOrientation(p1, p2, Point{2.0, 1.0}), 1); // Expect: ClockWise
    EXPECT_EQ(getOrientation(p1, p2, Point{1.0, 2.0}), 2); // Expect: CounterClockWise
}

TEST(PointsTest, GetDistance)
{
    Point p1{0.0, 0.0}, p2{2.0, 2.0};
    EXPECT_FLOAT_EQ(getDistance(p1, p2), 2.82842);
}
