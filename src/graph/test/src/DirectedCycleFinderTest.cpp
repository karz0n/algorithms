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
    read("assets/graph/graphWithoutDirectedCycle.txt", graph);

    DirectedCycleFinder finder{graph};
    EXPECT_FALSE(finder.hasCycle());

    const auto& cycle = finder.cycle();
    EXPECT_THAT(cycle, IsEmpty());
}

TEST(DigraphTest, DirectedCycleIsPresent)
{
    Digraph graph;
    read("assets/graph/graphWithDirectedCycle.txt", graph);

    DirectedCycleFinder finder{graph};
    EXPECT_TRUE(finder.hasCycle());
    EXPECT_THAT(finder.cycle(), ElementsAre(1, 3, 5, 1));
}