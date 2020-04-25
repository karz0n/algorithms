#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "RectCrossFinder.hpp"

using namespace algorithms;

using ::testing::SizeIs;
using ::testing::UnorderedElementsAre;
using ::testing::Pair;

TEST(RectCrossFinderTest, Find)
{
    RectCrossFinder finder;

    Rect r1{Point{1.0, 3.0}, Point{7.0, 1.0}};
    Rect r2{Point{3.0, 8.0}, Point{6.0, 2.0}};
    Rect r3{Point{5.0, 7.0}, Point{9.0, 5.0}};

    finder.add(r1);
    finder.add(r2);
    finder.add(r3);

    auto r = finder.find();
    ASSERT_THAT(r, SizeIs(2));
    // clang-format off
    EXPECT_THAT(r, UnorderedElementsAre(
       Pair(r1, r2),
       Pair(r2, r3)
    ));
    // clang-format on
}
