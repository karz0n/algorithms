#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "EagerPrimsMinSpanningTree.hpp"

using namespace testing;
using namespace algorithms;

TEST(EagerPrimsMinSpanningTreeTest, tinyGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/tinyEWG.txt", graph); });

    EagerPrimsMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(10.46351));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}

TEST(EagerPrimsMinSpanningTreeTest, mediumGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/mediumEWG.txt", graph); });

    EagerPrimsMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(20.7732));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}

TEST(EagerPrimsMinSpanningTreeTest, DISABLED_largeGraph /* Disabled due to long verifying */)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/largeEWG.txt", graph); });

    EagerPrimsMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(65.2407));

    EXPECT_NO_THROW(verifyMinSpanningTree(tree.edges(), graph));
}
