#include <gtest/gtest.h>

#include <LineSegment.hpp>

using namespace algorithms;

TEST(LineSegmentTest, IsVertical)
{
    LineSegment s{Point{1.0, 1.0}, Point{1.0, 2.0}};
    EXPECT_TRUE(s.isVertical());
    EXPECT_TRUE(s.isOrthogonal());
}

TEST(LineSegmentTest, IsHorizontal)
{
    LineSegment s{Point{1.0, 1.0}, Point{2.0, 1.0}};
    EXPECT_TRUE(s.isHorizontal());
    EXPECT_TRUE(s.isOrthogonal());
}
