#include <string>

#include <gtest/gtest.h>

#include "Common.hpp"
#include "UnionFind.hpp"

using namespace algorithms::uf;

static UnionFind createFromFile(const fs::path& path)
{
    UnionFind unionFind;

    Unions unions = readUnionsFromFile(path);
    auto time = measure([&] () {
        unionFind.reset(unions.size());
        for (const auto& u : unions) {
            if (!unionFind.connected(u.first, u.second)) {
                unionFind.associate(u.first, u.second);
            }
        }
    });
    printMeasure(path, unions.size(), time);

    return unionFind;
}

/**
 * Tests union find algorithm on little amount of unions.
 *
 * This test took: 0 milliseconds (2074 nanoseconds)
 */
TEST(UnionFind, tinyUnionFind)
{
    UnionFind unionFind = createFromFile(TINY_UNIONS_PATH);

    ASSERT_TRUE(unionFind.connected(4, 3));
    ASSERT_TRUE(unionFind.connected(9, 4));
    ASSERT_TRUE(unionFind.connected(6, 7));
}

/**
 * Tests union find algorithm on medium amount of unions.
 *
 * This test took: 0 milliseconds (58167 nanoseconds)
 */
TEST(UnionFind, mediumUnionFind)
{
    UnionFind unionFind = createFromFile(MEDIUM_UNIONS_PATH);

    ASSERT_TRUE(unionFind.connected(44, 43));
    ASSERT_TRUE(unionFind.connected(474, 473));
    ASSERT_TRUE(unionFind.connected(342, 341));
}

/**
 * Tests union find algorithm on large amount of unions.
 *
 * This test took: 290 milliseconds (290638026 nanoseconds)
 */
TEST(UnionFind, largeUnionFind)
{
    UnionFind unionFind = createFromFile(LARGE_UNIONS_PATH);

    ASSERT_TRUE(unionFind.connected(686513, 37739));
    ASSERT_TRUE(unionFind.connected(612504, 808506));
    ASSERT_TRUE(unionFind.connected(254379, 187449));
}
