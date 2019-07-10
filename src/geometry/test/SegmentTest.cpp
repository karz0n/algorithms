#include <gtest/gtest.h>

#include <Segment.hpp>

using namespace algorithms;

TEST(Segment, IsVertical)
{
    Segment s{Point{1.0, 1.0}, Point{1.0, 2.0}};
    EXPECT_TRUE(s.isVertical());
}

TEST(Segment, IsHorizontal)
{
    Segment s{Point{1.0, 1.0}, Point{2.0, 1.0}};
    EXPECT_TRUE(s.isHorizontal());
}
