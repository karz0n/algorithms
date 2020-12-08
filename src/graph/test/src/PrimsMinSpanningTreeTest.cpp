#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "PrimsMinSpanningTree.hpp"

using namespace testing;
using namespace algorithms;

TEST(PrimsMinSpanningTreeTest, tinyGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/tinyEWG.txt", graph); });

    PrimsMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(10.46351));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}

TEST(PrimsMinSpanningTreeTest, mediumGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/mediumEWG.txt", graph); });

    PrimsMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(20.7732));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}

TEST(PrimsMinSpanningTreeTest, DISABLED_largeGraph /* Disabled due to long verifying */)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/largeEWG.txt", graph); });

    PrimsMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(65.2407));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}
