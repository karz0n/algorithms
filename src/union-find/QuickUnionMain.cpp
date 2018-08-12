#include <string>

#include <gtest/gtest.h>

#include "Common.hpp"
#include "QuickUnion.hpp"

using namespace algorithms::uf;

QuickUnion readFromFile(const std::string& path)
{
    QuickUnion quickUnion;

    Unions unions = readUnionsFromFile(path);
    run([&] () {
        quickUnion.reset(unions.size());
        for (const auto& u : unions) {
            if (!quickUnion.connected(u.first, u.second)) {
                quickUnion.associate(u.first, u.second);
            }
        }
    });

    return quickUnion;
}

/**
 * Tests quick union algorithm on little amount of unions.
 *
 * This test took: 0 milliseconds (1738 nanoseconds)
 */
TEST(QuickUnion, tinyUnionFind)
{
    QuickUnion quickUnion = readFromFile("resources/union-find/tinyUF.txt");

    ASSERT_TRUE(quickUnion.connected(4, 3));
    ASSERT_TRUE(quickUnion.connected(9, 4));
    ASSERT_TRUE(quickUnion.connected(6, 7));
}

/**
 * Tests quick union algorithm on medium amount of unions.
 *
 * This test took: 0 milliseconds (132638 nanoseconds)
 */
TEST(QuickUnion, mediumUnionFind)
{
    QuickUnion quickUnion = readFromFile("resources/union-find/mediumUF.txt");

    ASSERT_TRUE(quickUnion.connected(44, 43));
    ASSERT_TRUE(quickUnion.connected(474, 473));
    ASSERT_TRUE(quickUnion.connected(342, 341));
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
    QuickUnion quickUnion = readFromFile("resources/union-find/largeUF.txt");

    ASSERT_TRUE(quickUnion.connected(686513, 37739));
    ASSERT_TRUE(quickUnion.connected(612504, 808506));
    ASSERT_TRUE(quickUnion.connected(254379, 187449));
}
