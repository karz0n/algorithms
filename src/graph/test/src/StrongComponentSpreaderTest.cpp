#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "StrongComponentSpreader.hpp"

using namespace algorithms;
using namespace testing;

class StrongComponentSpreaderTest : public Test {
public:
    void
    SetUp() override
    {
        read("assets/graph/strongComponents.txt", graph);
    }

public:
    Digraph graph;
};

TEST_F(StrongComponentSpreaderTest, IsConnected)
{
    StrongComponentSpreader spreader{graph};
    EXPECT_EQ(spreader.count(), 5);

    /* Check connection property of vertices within component */
    EXPECT_TRUE(spreader.connected(0, 2));
    EXPECT_TRUE(spreader.connected(2, 3));
    EXPECT_TRUE(spreader.connected(3, 4));
    EXPECT_TRUE(spreader.connected(4, 5));
}

TEST_F(StrongComponentSpreaderTest, BelongsToComponent)
{
    StrongComponentSpreader spreader{graph};
    EXPECT_EQ(spreader.count(), 5);

    /* Check relation to components */
    EXPECT_EQ(spreader.id(0), 1);
    EXPECT_EQ(spreader.id(1), 0);
    EXPECT_EQ(spreader.id(2), 1);
    EXPECT_EQ(spreader.id(3), 1);
    EXPECT_EQ(spreader.id(4), 1);
    EXPECT_EQ(spreader.id(5), 1);
    EXPECT_EQ(spreader.id(6), 3);
    EXPECT_EQ(spreader.id(7), 4);
    EXPECT_EQ(spreader.id(8), 3);
    EXPECT_EQ(spreader.id(9), 2);
    EXPECT_EQ(spreader.id(10), 2);
    EXPECT_EQ(spreader.id(11), 2);
    EXPECT_EQ(spreader.id(12), 2);
}