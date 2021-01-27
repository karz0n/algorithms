#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MsdRadixSort.hpp"

using namespace testing;
using namespace algorithms;

TEST(MsdRadixSortTest, Sort)
{
    StringViews input{"she",
                      "sells",
                      "seashells",
                      "by",
                      "the",
                      "sea",
                      "shore",
                      "the",
                      "shells",
                      "she",
                      "sells",
                      "are",
                      "surely",
                      "seashells"};

    MsdRadixSort::sort(input);

    // clang-format off
    EXPECT_THAT(input,ElementsAre(
        "are",
        "by",
        "sea",
        "seashells",
        "seashells",
        "sells",
        "sells",
        "she",
        "she",
        "shells",
        "shore",
        "surely",
        "the",
        "the"
    ));
    // clang-format on
}