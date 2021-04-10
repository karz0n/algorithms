#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SHA1.hpp"

using namespace testing;
using namespace algorithms;

TEST(Sha1Test, Hash)
{
    const std::string_view data{"Hash darling, hash!"};
    const auto digest = SHA1{}(data);
    EXPECT_THAT(digest.toString(), Eq("ee41d52950ad0354166bdecbea73f9aae5c91aae"));
}
