#include <gtest/gtest.h>

#include "Common.hpp"
#include "QuickFind.hpp"

using namespace algorithms;

/**
 * Tests quick find algorithm on little amount of unions.
 */
TEST(QuickFind, tinyUnionFind)
{
    auto set = makeSet<QuickFind>("TinyUnions", getTinyUnions());

    ASSERT_TRUE(set.connected(4, 3));
    ASSERT_TRUE(set.connected(9, 4));
    ASSERT_TRUE(set.connected(6, 7));
}

/**
 * Tests quick find algorithm on medium amount of unions.
 */
TEST(QuickFind, mediumUnionFind)
{
    auto set = makeSet<QuickFind>("MediumUnions", getMediumUnions());

    ASSERT_TRUE(set.connected(44, 43));
    ASSERT_TRUE(set.connected(474, 473));
    ASSERT_TRUE(set.connected(342, 341));
}

/**
 * Tests quick find algorithm on large amount of unions.
 *
 * This test took very long time therefore was disabled. To enable test
 * you should remove 'DISABLED_' from name.
 */
TEST(QuickFind, DISABLED_largeUnionFind)
{
    auto set = makeSet<QuickFind>("LargeUnions", getMediumUnions());

    ASSERT_TRUE(set.connected(686513, 37739));
    ASSERT_TRUE(set.connected(612504, 808506));
    ASSERT_TRUE(set.connected(254379, 187449));
}
