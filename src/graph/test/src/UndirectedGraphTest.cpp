#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <UndirectedGraph.hpp>

using namespace algorithms;

using ::testing::Contains;

class UndirectedGraphTest : public ::testing::Test {
protected:
    UndirectedGraphTest()
        : graph{2}
    {
    }

protected:
    UndirectedGraph graph;
};

TEST(UndirectedGraphTest, Properties)
{
    UndirectedGraph graph{2};
    graph.connect(0, 1);

    EXPECT_EQ(graph.verticesCount(), 2);
    EXPECT_EQ(graph.edgesCount(), 1);
}

TEST(UndirectedGraphTest, Connect)
{
    UndirectedGraph graph{2};
    graph.connect(1, 0);

    EXPECT_THAT(graph.adjacency(0), Contains(1));
    EXPECT_THAT(graph.adjacency(1), Contains(0));
}

TEST(UndirectedGraphTest, Degree)
{
    UndirectedGraph graph{2};
    graph.connect(0, 1);

    EXPECT_EQ(Graph::degree(graph, 0), 1);
    EXPECT_EQ(Graph::degree(graph, 1), 1);
}

TEST(UndirectedGraphTest, MaxDegree)
{
    UndirectedGraph graph{3};
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);

    EXPECT_EQ(UndirectedGraph::maxDegree(graph), 2);
}

TEST(UndirectedGraphTest, AverageDegree)
{
    UndirectedGraph graph{3};
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);

    EXPECT_EQ(UndirectedGraph::averageDegree(graph), 2.0);
}

TEST(UndirectedGraphTest, CountOfSelfLoop)
{
    UndirectedGraph graph{2};
    graph.connect(0, 0);
    graph.connect(1, 1);

    EXPECT_EQ(UndirectedGraph::countOfSelfLoop(graph), 2);
}