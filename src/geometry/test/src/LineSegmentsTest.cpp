#include <gtest/gtest.h>

#include <LineSegments.hpp>

using namespace algorithms;

TEST(LineSegmentsTest, Intersects)
{
    LineSegment s1;
    LineSegment s2;

    s1.p1 = {1.0, 1.0}, s1.p2 = {10.0, 1.0};
    s2.p1 = {1.0, 2.0}, s2.p2 = {10.0, 2.0};
    EXPECT_FALSE(intersects(s1, s2));

    s1.p1 = {10.0, 0.0}, s1.p2 = {0.0, 10.0};
    s2.p1 = {0.0, 0.0}, s2.p2 = {10.0, 10.0};
    EXPECT_TRUE(intersects(s1, s2));

    s1.p1 = {-5.0, -5.0}, s1.p2 = {0.0, 0.0};
    s2.p1 = {1.0, 1.0}, s2.p2 = {10.0, 10.0};
    EXPECT_FALSE(intersects(s1, s2));
}
