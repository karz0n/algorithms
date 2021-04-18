#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Points.hpp>

using namespace testing;
using namespace algorithms;

TEST(PointsTest, GetOrientation)
{
    Point p1{2.0, 2.0}, p2{1.0, 1.0};

    // Expect: Counterclockwise
    EXPECT_EQ(getOrientation(Point{3.0, 1.0}, Point{2.0, 2.0}, Point{1.0, 1.0}),
              +1 /* Counterclockwise */);
    EXPECT_EQ(getOrientation(Point{1.0, 1.0}, Point{2.0, 2.0}, Point{3.0, 1.0}),
              -1 /* Clockwise */);
    EXPECT_EQ(getOrientation(Point{1.0, 1.0}, Point{2.0, 2.0}, Point{3.0, 3.0}),
              0 /* Collinear */);
}

TEST(PointsTest, GetDistance)
{
    Point p1{0.0, 0.0}, p2{2.0, 2.0};
    EXPECT_THAT(getDistance(p1, p2), FloatNear(2.8284, 0.001));
}

TEST(PointsTest, CompareByX)
{
    Point p1{0.0, 0.0}, p2{2.0, 2.0};

    CompareByX comparator;
    EXPECT_THAT(comparator(p1, p2), IsTrue());
    EXPECT_THAT(comparator(p2, p1), IsFalse());
    EXPECT_THAT(comparator(p1, p1), IsFalse());
}

TEST(PointsTest, CompareByY)
{
    Point p1{0.0, 0.0}, p2{2.0, 2.0};

    CompareByX comparator;
    EXPECT_THAT(comparator(p1, p2), IsTrue());
    EXPECT_THAT(comparator(p2, p1), IsFalse());
    EXPECT_THAT(comparator(p1, p1), IsFalse());
}

TEST(PointsTest, CompareByXY)
{
    Point p1{0.0, 0.0}, p2{2.0, 0.0};

    CompareByXY comparator;
    EXPECT_THAT(comparator(p1, p2), IsTrue());
    EXPECT_THAT(comparator(p2, p1), IsFalse());
    EXPECT_THAT(comparator(p1, p1), IsFalse());
}

TEST(PointsTest, CompareByPolarOrder)
{
    Point p1{1.0, 1.0}, p2{3.0, 1.0};

    CompareByPolarOrder comparator1{Point{2.0, 2.0}};
    EXPECT_THAT(comparator1(p1, p2), IsTrue());
    CompareByPolarOrder comparator2{Point{2.0, 2.0}};
    EXPECT_THAT(comparator2(p2, p1), IsFalse());
}