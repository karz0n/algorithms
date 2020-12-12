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
    readGraph("assets/graph/graphWithoutDirectedCycle.txt", graph);

    Vertices vertices;
    for (auto v : TopologicalOrderIterator{graph}) {
        vertices.push_back(v);
    }

    EXPECT_THAT(vertices, ElementsAre(2, 3, 4, 5, 1, 0, 12, 11, 10, 9, 8, 6, 7));
}
