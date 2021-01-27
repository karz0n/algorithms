#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LsdRadixSort.hpp"

using namespace testing;
using namespace algorithms;

TEST(LsdRadixSortTest, Sort)
{
    StringViews input{
        "dab",
        "add",
        "cab",
        "fad",
        "fee",
        "bad",
        "dad",
        "bee",
        "fed",
        "bed",
    };

    LsdRadixSort::sort(input, 3);

    // clang-format off
    EXPECT_THAT(input,ElementsAre(
        "add",
        "bad",
        "bed",
        "bee",
        "cab",
        "dab",
        "dad",
        "fad",
        "fed",
        "fee"
    ));
    // clang-format on
}