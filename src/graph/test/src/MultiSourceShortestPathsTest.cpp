#include "MultiSourceShortestPaths.hpp"
#include "Digraph.hpp"
#include "Common.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace algorithms;

using ::testing::ElementsAre;

TEST(MultiSourceShortestPaths, Dummy)
{
    Digraph graph;
    readGraph("assets/graph/multiSourceShortestPaths.txt", graph);

    MultiSourceShortestPaths paths{graph, {0, 4} /* Target vertices */};
    /* Distance from one of the source vertex (index of distance array) to the target vertices */
    EXPECT_THAT(paths.distances(), ElementsAre(0, 1, 1, 1, 0, 1));
}