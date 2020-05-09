#include <gtest/gtest.h>

#include "Common.hpp"

#include <Connector.hpp>

using namespace algorithms;

TEST(ConnectorTest, IsConnected)
{
    auto graph = read("assets/graph/tinyG.txt");

    Connector c{graph};

    EXPECT_TRUE(c.connected(0, 2));
    EXPECT_TRUE(c.connected(5, 3));
    EXPECT_TRUE(c.connected(7, 8));

    EXPECT_FALSE(c.connected(4, 10));
    EXPECT_FALSE(c.connected(1, 11));
    EXPECT_FALSE(c.connected(2, 12));
}

TEST(ConnectorTest, BelongsToComponent)
{
    auto graph = read("assets/graph/tinyG.txt");

    Connector c{graph};

    auto id1 = c.id(4);
    auto id2 = c.id(7);
    auto id3 = c.id(9);

    EXPECT_TRUE(id1 != id2 != id3);
}
