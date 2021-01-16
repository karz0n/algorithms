#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "Digraph.hpp"
#include "TopologicalOrderIterator.hpp"

using namespace algorithms;
using namespace testing;

TEST(TopologicalOrderIteratorTest, TopologicalSorting)
{
    Digraph graph;
    read("assets/graph/graphWithoutDirectedCycle.txt", graph);

    Vertices vertices;
    for (auto v : TopologicalOrderIterator{graph}) {
        vertices.push_back(v);
    }

    EXPECT_THAT(vertices, ElementsAre(7, 6, 8, 9, 10, 11, 12, 0, 1, 5, 4, 3, 2));
}
