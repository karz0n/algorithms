#include "DepthFirstOrder.hpp"
#include "Common.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace algorithms;

using ::testing::ElementsAre;

TEST(DepthFirstOrderTest, TopologicalSortNegative)
{
    Digraph graph;
    readGraph("assets/graph/graphWithDirectedCycle.txt", graph);

    EXPECT_ANY_THROW({ DepthFirstOrder order(graph, true); });
}

TEST(DepthFirstOrderTest, TopologicalSortPositive)
{
    Digraph graph;
    readGraph("assets/graph/graphWithoutDirectedCycle.txt", graph);

    EXPECT_NO_THROW({
        DepthFirstOrder order{graph};
        EXPECT_THAT(order.reversePost(), ElementsAre(2, 3, 4, 5, 1, 0, 12, 11, 10, 9, 8, 6, 7));
    });
}
