#include "Common.hpp"
#include "ComponentSpreader.hpp"
#include "Digraph.hpp"
#include "UndirectedGraph.hpp"

#include <gtest/gtest.h>

using namespace algorithms;

template<typename T>
class ConnectorTest : public ::testing::Test {
public:
    void
    SetUp() override
    {
        read("assets/graph/tinyG.txt", graph);
    }

public:
    T graph;
};

using TestTypes = ::testing::Types<Digraph, UndirectedGraph>;
TYPED_TEST_SUITE(ConnectorTest, TestTypes);

TYPED_TEST(ConnectorTest, IsConnected)
{
    ComponentSpreader c{this->graph};

    EXPECT_TRUE(c.connected(0, 2));
    EXPECT_TRUE(c.connected(5, 3));
    EXPECT_TRUE(c.connected(7, 8));

    EXPECT_FALSE(c.connected(4, 10));
    EXPECT_FALSE(c.connected(1, 11));
    EXPECT_FALSE(c.connected(2, 12));
}

TYPED_TEST(ConnectorTest, BelongsToComponent)
{
    ComponentSpreader c{this->graph};

    auto id1 = c.id(4);
    auto id2 = c.id(7);
    auto id3 = c.id(9);

    EXPECT_TRUE(id1 != id2 != id3);
}
