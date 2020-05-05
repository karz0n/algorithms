#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"

using namespace algorithms;

using ::testing::Contains;

class GraphTest : public ::testing::Test {
protected:
    Graph _graph;
};

TEST_F(GraphTest, Properties)
{
    _graph.reset(2);

    EXPECT_EQ(_graph.vertices(), 2);
    EXPECT_EQ(_graph.edges(), 0);
}

TEST_F(GraphTest, Connect)
{
    _graph.reset(2);
    _graph.connect(0, 1);

    EXPECT_THAT(_graph.adjacency(0), Contains(1));
    EXPECT_THAT(_graph.adjacency(1), Contains(0));
    EXPECT_EQ(_graph.vertices(), 2);
    EXPECT_EQ(_graph.edges(), 1);
}
