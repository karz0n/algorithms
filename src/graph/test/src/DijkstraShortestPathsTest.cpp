#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "DijkstraShortestPaths.hpp"

using namespace testing;
using namespace algorithms;

class DijkstraShortestPathsTest : public TestWithParam<EdgeWeightedDigraph> {
public:
    DijkstraShortestPathsTest()
        : paths{GetParam(), source()}
    {
    }

    static std::size_t
    source()
    {
        return 0;
    }

public:
    DijkstraShortestPaths paths;
};

INSTANTIATE_TEST_SUITE_P(DijkstraShortestPaths,
                         DijkstraShortestPathsTest,
                         Values(readEdgeWeightedDigraph("assets/graph/tinyEWD.txt"),
                                readEdgeWeightedDigraph("assets/graph/mediumEWG.txt"),
                                readEdgeWeightedDigraph("assets/graph/largeEWG.txt")));

Matcher<const DirectedEdge&>
isNegative()
{
    return Property(&DirectedEdge::weight, Lt(0.0));
}

TEST_P(DijkstraShortestPathsTest, NegativeEdgeIsAbsent)
{
    const auto& graph = GetParam().edges();
    EXPECT_THAT(graph, Not(Contains(isNegative())));
}

TEST_P(DijkstraShortestPathsTest, EdgesDistancesAreConsistency)
{
    const auto& graph = GetParam();
    for (std::size_t v = 0; v < graph.verticesCount(); ++v) {
        if (v == source()) {
            EXPECT_EQ(paths.edgeTo(v), DijkstraShortestPaths::EdgeOrNull{});
            EXPECT_EQ(paths.distanceTo(v), DijkstraShortestPaths::minDistance());
            continue;
        }
        if (!paths.hasPathTo(v) && paths.distanceTo(v) != DijkstraShortestPaths::maxDistance()) {
            FAIL() << "Inconsistency detected at " << v << " vertex";
        }
    }
}

TEST_P(DijkstraShortestPathsTest, CondityionsAreMetForEdges)
{
    for (std::size_t v = 0; v < GetParam().verticesCount(); ++v) {
        for (const auto& edge : GetParam().adjacency(v)) {
            const std::size_t w{edge.to()};
            if (paths.distanceTo(v) + edge.weight() < paths.distanceTo(w)) {
                FAIL() << "Optimality conditions not satisfied at: " << edge.toString();
            }
        }
    }
}

TEST_P(DijkstraShortestPathsTest, CondityionsAreMetForTreeEdges)
{
    for (std::size_t w = 0; w < GetParam().verticesCount(); ++w) {
        const auto edge = paths.edgeTo(w);
        if (!edge) {
            continue;
        }
        const std::size_t v{edge->from()};
        if (paths.distanceTo(v) + edge->weight() != paths.distanceTo(w)) {
            FAIL() << "Optimality conditions not satisfied at: " << edge->toString();
        }
    }
}
