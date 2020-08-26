#include <gtest/gtest.h>

#include "Common.hpp"
#include "UnionFind.hpp"

using namespace algorithms;

/**
 * Tests union find algorithm on little amount of unions.
 *
 * This test took: 0 milliseconds (2074 nanoseconds)
 */
TEST(UnionFind, tinyUnionFind)
{
    auto set = makeSet<UnionFind>("TinyUnions", getTinyUnions());

    ASSERT_TRUE(set.connected(4, 3));
    ASSERT_TRUE(set.connected(9, 4));
    ASSERT_TRUE(set.connected(6, 7));
}

/**
 * Tests union find algorithm on medium amount of unions.
 *
 * This test took: 0 milliseconds (58167 nanoseconds)
 */
TEST(UnionFind, mediumUnionFind)
{
    auto set = makeSet<UnionFind>("MediumUnions", getMediumUnions());

    ASSERT_TRUE(set.connected(44, 43));
    ASSERT_TRUE(set.connected(474, 473));
    ASSERT_TRUE(set.connected(342, 341));
}

/**
 * Tests union find algorithm on large amount of unions.
 *
 * This test took: 290 milliseconds (290638026 nanoseconds)
 */
TEST(UnionFind, largeUnionFind)
{
    auto set = makeSet<UnionFind>("LargeUnions", getLargeUnions());

    ASSERT_TRUE(set.connected(686513, 37739));
    ASSERT_TRUE(set.connected(612504, 808506));
    ASSERT_TRUE(set.connected(254379, 187449));
}
