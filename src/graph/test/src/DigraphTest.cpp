#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Digraph.hpp"

using namespace algorithms;
using namespace testing;

TEST(DigraphTest, Properties)
{
    Digraph graph{2};
    graph.connect(0, 1);

    EXPECT_EQ(graph.verticesCount(), 2);
    EXPECT_EQ(graph.edgesCount(), 1);
}

TEST(DigraphTest, Connect)
{
    Digraph graph{2};
    graph.connect(1, 0);

    EXPECT_THAT(graph.adjacency(0).empty(), IsTrue());
    EXPECT_THAT(graph.adjacency(1), ElementsAre(0));

    graph.connect(0, 1);

    EXPECT_THAT(graph.adjacency(0), ElementsAre(1));
    EXPECT_THAT(graph.adjacency(1), ElementsAre(0));
}

TEST(DigraphTest, Reverse)
{
    Digraph graph{5};
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

TEST(DigraphTest, Degree)
{
    Digraph graph{2};
    graph.connect(0, 1);

    EXPECT_EQ(Graph::degree(graph, 0), 1);
    EXPECT_EQ(Graph::degree(graph, 1), 0);
}

TEST(DigraphTest, MaxDegree)
{
    Digraph graph{3};
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);

    EXPECT_EQ(Digraph::maxDegree(graph), 2);
}

TEST(DigraphTest, AverageDegree)
{
    Digraph graph{3};
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);

    EXPECT_EQ(Digraph::averageDegree(graph), 1.0);
}

TEST(DigraphTest, CountOfSelfLoop)
{
    Digraph graph{2};
    graph.connect(0, 0);
    graph.connect(1, 1);

    EXPECT_EQ(Digraph::countOfSelfLoop(graph), 2);
}