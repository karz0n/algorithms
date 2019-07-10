#include <gtest/gtest.h>

#include <Point.hpp>

using namespace algorithms;

TEST(Point, Orient)
{
    Point p1{0.0, 0.0}, p2{4.0, 4.0};

    EXPECT_EQ(p1.orientTo(p2, Point{1.0, 1.0}), 0); // Expect: Colinear
    EXPECT_EQ(p1.orientTo(p2, Point{2.0, 1.0}), 1); // Expect: ClockWise
    EXPECT_EQ(p1.orientTo(p2, Point{1.0, 2.0}), 2); // Expect: CounterClockWise
}
