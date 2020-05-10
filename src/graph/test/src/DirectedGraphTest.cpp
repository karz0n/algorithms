#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <DirectedGraph.hpp>

using namespace algorithms;

using ::testing::Contains;
using ::testing::IsEmpty;

class DirectedGraphTest : public ::testing::Test {
protected:
    DirectedGraphTest()
        : graph{2}
    {
    }

protected:
    DirectedGraph graph;
};

TEST_F(DirectedGraphTest, Properties)
{
    graph.connect(0, 1);

    EXPECT_EQ(graph.verticesCount(), 2);
    EXPECT_EQ(graph.edgesCount(), 1);
}

TEST_F(DirectedGraphTest, Connect)
{
    graph.connect(1, 0);

    // EXPECT_THAT(graph.adjacency(0), IsEmpty());
    EXPECT_THAT(graph.adjacency(1), Contains(0));

    graph.connect(0, 1);

    EXPECT_THAT(graph.adjacency(0), Contains(1));
    EXPECT_THAT(graph.adjacency(1), Contains(0));
}
