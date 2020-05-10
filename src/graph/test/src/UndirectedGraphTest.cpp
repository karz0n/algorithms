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

TEST_F(UndirectedGraphTest, Properties)
{
    graph.connect(0, 1);

    EXPECT_EQ(graph.verticesCount(), 2);
    EXPECT_EQ(graph.edgesCount(), 1);
}

TEST_F(UndirectedGraphTest, Connect)
{
    graph.connect(1, 0);

    EXPECT_THAT(graph.adjacency(0), Contains(1));
    EXPECT_THAT(graph.adjacency(1), Contains(0));
}
