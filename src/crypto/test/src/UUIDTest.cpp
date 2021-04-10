#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "UUID.hpp"

using namespace testing;
using namespace algorithms;

TEST(UUIDTest, ByTime)
{
    const auto uuid = UUID::createByTime().toString();
    EXPECT_THAT(uuid, Not(IsEmpty()));
}

TEST(UUIDTest, ByRandom)
{
    const auto uuid = UUID::createByRandom().toString();
    EXPECT_THAT(uuid, Not(IsEmpty()));
}

TEST(UUIDTest, ByName)
{
    const auto uuid = UUID::createByName(UUID::dns(), "www.example.com").toString();
    EXPECT_THAT(uuid, Not(IsEmpty()));
}