#include <iostream>
#include <string>
#include <chrono>

#include <gtest/gtest.h>

#include "Common.hpp"
#include "QuickFind.hpp"

using namespace algorithms::uf;

QuickFind readFromFile(const std::string& path)
{
    QuickFind quickFind;

    Unions unions = readUnionsFromFile(path);
    auto time = measure([&] () {
        quickFind.reset(unions.size());
        for (const auto& u : unions) {
            if (!quickFind.connected(u.first, u.second)) {
                quickFind.associate(u.first, u.second);
            }
        }
    });

    std::cout << "Processing: '" << path << "' took: " << formatTime(time) << std::endl;

    return quickFind;
}

/**
 * Tests quick find algorithm on little amount of unions.
 */
TEST(QuickFind, tinyUnionFind)
{
    QuickFind quickFind = readFromFile("resources/union-find/tinyUF.txt");

    ASSERT_TRUE(quickFind.connected(4, 3));
    ASSERT_TRUE(quickFind.connected(9, 4));
    ASSERT_TRUE(quickFind.connected(6, 7));
}

/**
 * Tests quick find algorithm on medium amount of unions.
 */
TEST(QuickFind, mediumUnionFind)
{
    QuickFind quickFind = readFromFile("resources/union-find/mediumUF.txt");

    ASSERT_TRUE(quickFind.connected(44, 43));
    ASSERT_TRUE(quickFind.connected(474, 473));
    ASSERT_TRUE(quickFind.connected(342, 341));
}

/**
 * Tests quick find algorithm on large amount of unions.
 *
 * This test took very long time therefore was disabled. To enable test
 * you should remove 'DISABLED_' from name.
 */
TEST(QuickFind, DISABLED_largeUnionFind)
{
    QuickFind quickFind = readFromFile("resources/union-find/largeUF.txt");

    ASSERT_TRUE(quickFind.connected(686513, 37739));
    ASSERT_TRUE(quickFind.connected(612504, 808506));
    ASSERT_TRUE(quickFind.connected(254379, 187449));
}


