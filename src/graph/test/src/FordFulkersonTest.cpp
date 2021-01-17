#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "FordFulkerson.hpp"

using namespace testing;
using namespace algorithms;

TEST(FordFulkersonTest, TinyFlowNetwork)
{
    FlowNetwork network;
    read("assets/graph/tinyFN.txt", network);

    FordFulkerson maxFlow{network, 0, network.verticesCount() - 1};
    EXPECT_THAT(maxFlow.value(), DoubleEq(4.0));
    EXPECT_THAT(maxFlow.minCut(), ElementsAre(0, 2));
}
