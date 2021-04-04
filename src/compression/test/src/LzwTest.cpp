#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Lzw.hpp"

using namespace testing;
using namespace algorithms;

TEST(LzwTest, Reconstruction)
{
    static const std::string_view text{"Peter Piper picked a peck of pickled peppers\n"
                                       "A peck of pickled peppers Peter Piper picked\n"
                                       "If Peter Piper picked a peck of pickled peppers\n"
                                       "Where's the peck of pickled peppers Peter Piper picked?"};

    const auto enData = lzw::encode(text);
    const auto deData = lzw::decode(enData);
    EXPECT_EQ(deData, text);
}