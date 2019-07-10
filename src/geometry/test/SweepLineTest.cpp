#include <gtest/gtest.h>

#include <SweepLine.hpp>

using namespace algorithms;

TEST(SweepLine, PositiveSearch)
{
    Segments segments;
    segments.emplace_back(Point{1.0, 1.0}, Point{5.0, 1.0});
    segments.emplace_back(Point{3.0, 2.0}, Point{3.0, 4.0});
    segments.emplace_back(Point{4.0, 3.0}, Point{9.0, 3.0});
    segments.emplace_back(Point{7.0, 2.0}, Point{7.0, 5.0});

    Points points{Point{7.0, 3.0}};
    EXPECT_EQ(orthogonalSegmentIntersection(segments), points);
}
