#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TernarySearchTries.hpp"

using namespace algorithms;
using namespace testing;

TEST(TernarySearchTriesTest, Erase)
{
    TernarySearchTries tree;
    tree.put("shells", 3);
    tree.put("she", 2);
    tree.put("shore", 7);

    tree.erase("she");

    EXPECT_THAT(tree.has("she"), IsFalse());
    EXPECT_THAT(tree.has("shells"), IsTrue());
    EXPECT_THAT(tree.has("shore"), IsTrue());
}

TEST(TernarySearchTriesTest, Update)
{
    TernarySearchTries tree;
    tree.put("shells", 3);
    tree.put("she", 2);

    EXPECT_THAT(tree.get("shells"), 3);
    EXPECT_THAT(tree.get("she"), 2);

    tree.put("shells", 1);
    tree.put("she", 0);

    EXPECT_THAT(tree.get("shells"), 1);
    EXPECT_THAT(tree.get("she"), 0);
}

TEST(TernarySearchTriesTest, Keys)
{
    TernarySearchTries tree;
    tree.put("shells", 3);
    tree.put("she", 2);
    tree.put("by", 1);
    EXPECT_THAT(tree.keys(), UnorderedElementsAre("shells", "she", "by"));
    tree.erase("shells");
    EXPECT_THAT(tree.keys(), UnorderedElementsAre("she", "by"));
}

TEST(TernarySearchTriesTest, KeysWithPrefix)
{
    TernarySearchTries tree;
    tree.put("shells", 3);
    tree.put("shore", 7);
    tree.put("she", 2);
    EXPECT_THAT(tree.keysWithPrefix("she"), UnorderedElementsAre("shells", "she"));
}

TEST(TernarySearchTriesTest, KeysThatMatch)
{
    TernarySearchTries tree;
    tree.put("shells", 3);
    tree.put("she", 2);
    tree.put("sea", 6);
    EXPECT_THAT(tree.keysThatMatch("s.."), UnorderedElementsAre("she", "sea"));
}

TEST(TernarySearchTriesTest, LongestPrefixOf)
{
    TernarySearchTries tree;
    tree.put("shell", 3);
    EXPECT_EQ(tree.longestPrefixOf("shellsort"), "shell");
    tree.put("shellso", 2);
    EXPECT_EQ(tree.longestPrefixOf("shellsort"), "shellso");
}

