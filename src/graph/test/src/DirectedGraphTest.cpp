#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "DirectedGraph.hpp"

using namespace algorithms;

using ::testing::ElementsAre;
using ::testing::IsTrue;

TEST(DirectedGraphTest, Properties)
{
    DirectedGraph graph{2};
    graph.connect(0, 1);

    EXPECT_EQ(graph.verticesCount(), 2);
    EXPECT_EQ(graph.edgesCount(), 1);
}

TEST(DirectedGraphTest, Connect)
{
    DirectedGraph graph{2};
    graph.connect(1, 0);

    EXPECT_THAT(graph.adjacency(0).empty(), IsTrue());
    EXPECT_THAT(graph.adjacency(1), ElementsAre(0));

    graph.connect(0, 1);

    EXPECT_THAT(graph.adjacency(0), ElementsAre(1));
    EXPECT_THAT(graph.adjacency(1), ElementsAre(0));
}

TEST(DirectedGraphTest, Reverse)
{
    DirectedGraph graph{5};
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(3, 0);
    graph.connect(4, 3);

    auto reverseGraph = graph.reverse();
    EXPECT_THAT(reverseGraph.adjacency(0), ElementsAre(3));
    EXPECT_THAT(reverseGraph.adjacency(1), ElementsAre(0));
    EXPECT_THAT(reverseGraph.adjacency(2), ElementsAre(1));
    EXPECT_THAT(reverseGraph.adjacency(3), ElementsAre(4));
    EXPECT_THAT(reverseGraph.adjacency(4).empty(), IsTrue());
}

TEST(DirectedGraphTest, hasCyclePositive)
{
    DirectedGraph graph;
    readGraph("assets/graph/graphWithoutDirectedCycle.txt", graph);
    EXPECT_FALSE(DirectedGraph::hasCycle(graph));
}

TEST(DirectedGraphTest, hasCycleNegative)
{
    DirectedGraph graph;
    readGraph("assets/graph/graphWithDirectedCycle.txt", graph);
    EXPECT_TRUE(DirectedGraph::hasCycle(graph));
}

TEST(DirectedGraphTest, Degree)
{
    DirectedGraph graph{2};
    graph.connect(0, 1);

    EXPECT_EQ(Graph::degree(graph, 0), 1);
    EXPECT_EQ(Graph::degree(graph, 1), 0);
}

TEST(DirectedGraphTest, MaxDegree)
{
    DirectedGraph graph{3};
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);

    EXPECT_EQ(DirectedGraph::maxDegree(graph), 2);
}

TEST(DirectedGraphTest, AverageDegree)
{
    DirectedGraph graph{3};
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);

    EXPECT_EQ(DirectedGraph::averageDegree(graph), 1.0);
}

TEST(DirectedGraphTest, CountOfSelfLoop)
{
    DirectedGraph graph{2};
    graph.connect(0, 0);
    graph.connect(1, 1);

    EXPECT_EQ(DirectedGraph::countOfSelfLoop(graph), 2);
}