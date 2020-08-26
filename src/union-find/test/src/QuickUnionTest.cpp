#include <gtest/gtest.h>

#include "Common.hpp"
#include "QuickUnion.hpp"

using namespace algorithms;

/**
 * Tests quick union algorithm on little amount of unions.
 *
 * This test took: 0 milliseconds (1738 nanoseconds)
 */
TEST(QuickUnion, tinyUnionFind)
{
    auto set = makeSet<QuickUnion>("TinyUnions", getTinyUnions());

    ASSERT_TRUE(set.connected(4, 3));
    ASSERT_TRUE(set.connected(9, 4));
    ASSERT_TRUE(set.connected(6, 7));
}

/**
 * Tests quick union algorithm on medium amount of unions.
 *
 * This test took: 0 milliseconds (132638 nanoseconds)
 */
TEST(QuickUnion, mediumUnionFind)
{
    auto set = makeSet<QuickUnion>("MediumUnions", getMediumUnions());

    ASSERT_TRUE(set.connected(44, 43));
    ASSERT_TRUE(set.connected(474, 473));
    ASSERT_TRUE(set.connected(342, 341));
}

/**
 * Tests quick union algorithm on large amount of unions.
 *
 * This test took: ~
 *
 * This test took very long time therefore was disabled. To enable test
 * you should remove 'DISABLED_' from name.
 */
TEST(QuickUnion, DISABLED_largeUnionFind)
{
    auto set = makeSet<QuickUnion>("LargeUnions", getLargeUnions());

    ASSERT_TRUE(set.connected(686513, 37739));
    ASSERT_TRUE(set.connected(612504, 808506));
    ASSERT_TRUE(set.connected(254379, 187449));
}
