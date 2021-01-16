#include "DepthFirstOrder.hpp"
#include "Common.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace algorithms;
using namespace testing;

TEST(DepthFirstOrderTest, TopologicalSortNegative)
{
    Digraph graph;
    read("assets/graph/graphWithDirectedCycle.txt", graph);

    EXPECT_ANY_THROW({ DepthFirstOrder order(graph, true); });
}

TEST(DepthFirstOrderTest, TopologicalSortPositive)
{
    Digraph graph;
    read("assets/graph/graphWithoutDirectedCycle.txt", graph);

    DepthFirstOrder order{graph};

    EXPECT_THAT(order.pre(), ElementsAre(0, 5, 4, 2, 3, 1, 6, 9, 11, 12, 10, 8, 7));

    EXPECT_EQ(order.pre(0), 0);
    EXPECT_EQ(order.pre(5), 1);
    EXPECT_EQ(order.pre(4), 2);
    EXPECT_EQ(order.pre(2), 3);
    EXPECT_EQ(order.pre(3), 4);
    EXPECT_EQ(order.pre(1), 5);
    EXPECT_EQ(order.pre(6), 6);
    EXPECT_EQ(order.pre(9), 7);
    EXPECT_EQ(order.pre(11), 8);
    EXPECT_EQ(order.pre(12), 9);
    EXPECT_EQ(order.pre(10), 10);
    EXPECT_EQ(order.pre(8), 11);
    EXPECT_EQ(order.pre(7), 12);

    EXPECT_THAT(order.post(), ElementsAre(2, 3, 4, 5, 1, 0, 12, 11, 10, 9, 8, 6, 7));
    EXPECT_EQ(order.post(2), 0);
    EXPECT_EQ(order.post(3), 1);
    EXPECT_EQ(order.post(4), 2);
    EXPECT_EQ(order.post(5), 3);
    EXPECT_EQ(order.post(1), 4);
    EXPECT_EQ(order.post(0), 5);
    EXPECT_EQ(order.post(12), 6);
    EXPECT_EQ(order.post(11), 7);
    EXPECT_EQ(order.post(10), 8);
    EXPECT_EQ(order.post(9), 9);
    EXPECT_EQ(order.post(8), 10);
    EXPECT_EQ(order.post(6), 11);
    EXPECT_EQ(order.post(7), 12);

    EXPECT_THAT(order.reversePost(), ElementsAre(7, 6, 8, 9, 10, 11, 12, 0, 1, 5, 4, 3, 2));
}
