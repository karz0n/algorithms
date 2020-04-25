#include <gtest/gtest.h>

#include <Point.hpp>

using namespace algorithms;

TEST(PointTest, Equal)
{
    Point p1{1.0, 1.0}, p2{1.0, 1.0};
    EXPECT_TRUE(p1.equalByX(p2));
    EXPECT_TRUE(p1.equalByY(p2));
    EXPECT_EQ(p1, p2);

    Point p3{1.0, 2.0}, p4{2.0, 1.0};
    EXPECT_FALSE(p3.equalByX(p4));
    EXPECT_FALSE(p3.equalByY(p4));
    EXPECT_NE(p3, p4);
}
