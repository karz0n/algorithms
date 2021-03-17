#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "RegExpMatcher.hpp"

using namespace testing;
using namespace algorithms;

TEST(RegExpMatcherTest, PositiveMatch)
{
    RegExpMatcher matcher("((A*B|AC)D)");
    EXPECT_THAT(matcher.match("AAABD"), IsTrue());
    EXPECT_THAT(matcher.match("ACD"), IsTrue());
}

TEST(RegExpMatcherTest, NegativeMatch)
{
    RegExpMatcher matcher("((A*B|AC)D)");
    EXPECT_THAT(matcher.match("AAAAA"), IsFalse());
    EXPECT_THAT(matcher.match("AACCD"), IsFalse());
}