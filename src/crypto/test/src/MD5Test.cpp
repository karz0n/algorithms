#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MD5.hpp"

using namespace algorithms;
using namespace testing;

TEST(Md5Test, Hash)
{
    const std::string_view data{"Hash darling, hash!"};
    const auto digest = MD5{}(data);
    EXPECT_THAT(digest.toString(), Eq("6b3ec4ee2ebcf84058081fa3c1f9ad2f"));
}