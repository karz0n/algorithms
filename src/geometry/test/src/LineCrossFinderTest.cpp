#include <gtest/gtest.h>

#include "LineCrossFinder.hpp"

using namespace algorithms;

TEST(LineCrossFinderTest, Test)
{
    LineCrossFinder finder;
    finder.add(LineSegment{Point{1.0, 1.0}, Point{5.0, 1.0}});
    finder.add(LineSegment{Point{3.0, 2.0}, Point{3.0, 4.0}});
    finder.add(LineSegment{Point{4.0, 3.0}, Point{9.0, 3.0}});
    finder.add(LineSegment{Point{7.0, 2.0}, Point{7.0, 5.0}});

    Points points{Point{7.0, 3.0}};
    EXPECT_EQ(finder.find(), points);
}
