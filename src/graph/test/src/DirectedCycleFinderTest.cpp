#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "Digraph.hpp"
#include "DirectedCycleFinder.hpp"

using namespace algorithms;
using namespace testing;

TEST(DigraphTest, DirectedCycleIsAbsent)
{
    Digraph graph;
    readGraph("assets/graph/graphWithoutDirectedCycle.txt", graph);

    DirectedCycleFinder finder{graph};
    EXPECT_FALSE(finder.hasCycle());

    const auto& cycle = finder.cycle();
    EXPECT_THAT(cycle, IsEmpty());
}

TEST(DigraphTest, DirectedCycleIsPresent)
{
    Digraph graph;
    readGraph("assets/graph/graphWithDirectedCycle.txt", graph);

    DirectedCycleFinder finder{graph};
    EXPECT_TRUE(finder.hasCycle());

    const auto& cycle = finder.cycle();
    EXPECT_THAT(cycle, ElementsAre(5, 1, 3, 5));
}