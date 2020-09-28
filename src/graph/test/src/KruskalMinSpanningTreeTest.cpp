#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "KruskalMinSpanningTree.hpp"
#include "Common.hpp"

using namespace testing;
using namespace algorithms;

TEST(KruskalMinSpanningTreeTest, tinyGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/tinyEWG.txt", graph); });

    KruskalMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
}

TEST(KruskalMinSpanningTreeTest, mediumGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/mediumEWG.txt", graph); });

    KruskalMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
}

TEST(KruskalMinSpanningTreeTest, largeGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ readGraph("assets/graph/largeEWG.txt", graph); });

    KruskalMinSpanningTree tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
}
