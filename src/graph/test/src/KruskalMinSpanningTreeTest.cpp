#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "KruskalMinSpanningTree.hpp"

using namespace testing;
using namespace algorithms;

TEST(KruskalMinSpanningTreeTest, tinyGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/tinyEWG.txt", graph); });

    KruskalMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleNear(10.46351, 0.0001));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}

TEST(KruskalMinSpanningTreeTest, mediumGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/mediumEWG.txt", graph); });

    KruskalMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleNear(20.7732, 0.0001));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}

TEST(KruskalMinSpanningTreeTest, DISABLED_largeGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/largeEWG.txt", graph); });

    KruskalMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleNear(65.2407, 0.0001));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}
