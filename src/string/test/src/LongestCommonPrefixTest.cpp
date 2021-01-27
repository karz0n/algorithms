#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LongestCommonPrefix.hpp"

using namespace testing;
using namespace algorithms;

TEST(LongestCommonPrefixTest, Find)
{
    static std::string_view input{"Peter Piper picked a peck of pickled peppers"
                                  "A peck of pickled peppers Peter Piper picked"
                                  "If Peter Piper picked a peck of pickled peppers"
                                  "Where’s the peck of pickled peppers Peter Piper picked?"};

    auto output = LongestCommonPrefix::find(input);

    EXPECT_THAT(output, Eq("Peter Piper picked a peck of pickled peppers"));
}