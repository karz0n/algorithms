#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "BellmanFordShortestPaths.hpp"

#include <cmath>

using namespace algorithms;
using namespace testing;

class BellmanFordShortestPathsTest : public Test {
public:
    static std::size_t
    source()
    {
        return 0;
    }
};

static Matcher<const DirectedEdge&>
matchToFrom(const std::size_t from, const std::size_t to)
{
    return AllOf(Property(&DirectedEdge::from, from), Property(&DirectedEdge::to, to));
}

TEST_F(BellmanFordShortestPathsTest, WithoutNegaticeCycle)
{
    auto graph = readEdgeWeightedDigraph("assets/graph/tinyEWDn.txt");

    BellmanFordShortestPaths paths(graph, source());
    EXPECT_FALSE(paths.hasPathTo(0));

    EXPECT_TRUE(paths.hasPathTo(1));
    // clang-format off
    EXPECT_THAT(paths.pathTo(1), ElementsAre(
        matchToFrom(0, 2),
        matchToFrom(2, 7),
        matchToFrom(7, 3),
        matchToFrom(3, 6),
        matchToFrom(6, 4),
        matchToFrom(4, 5),
        matchToFrom(5, 1)
    ));
    // clang-format on

    EXPECT_TRUE(paths.hasPathTo(2));
    // clang-format off
    EXPECT_THAT(paths.pathTo(2), ElementsAre(
        matchToFrom(0, 2)
    ));
    // clang-format on

    EXPECT_TRUE(paths.hasPathTo(3));
    // clang-format off
    EXPECT_THAT(paths.pathTo(3), ElementsAre(
        matchToFrom(0, 2),
        matchToFrom(2, 7),
        matchToFrom(7, 3)
    ));
    // clang-format on

    EXPECT_TRUE(paths.hasPathTo(4));
    // clang-format off
    EXPECT_THAT(paths.pathTo(4), ElementsAre(
        matchToFrom(0, 2),
        matchToFrom(2, 7),
        matchToFrom(7, 3),
        matchToFrom(3, 6),
        matchToFrom(6, 4)
    ));
    // clang-format on

    EXPECT_TRUE(paths.hasPathTo(5));
    // clang-format off
    EXPECT_THAT(paths.pathTo(5), ElementsAre(
        matchToFrom(0, 2),
        matchToFrom(2, 7),
        matchToFrom(7, 3),
        matchToFrom(3, 6),
        matchToFrom(6, 4),
        matchToFrom(4, 5)
    ));
    // clang-format on

    EXPECT_TRUE(paths.hasPathTo(6));
    // clang-format off
    EXPECT_THAT(paths.pathTo(6), ElementsAre(
        matchToFrom(0, 2),
        matchToFrom(2, 7),
        matchToFrom(7, 3),
        matchToFrom(3, 6)
    ));
    // clang-format on

    EXPECT_TRUE(paths.hasPathTo(7));
    // clang-format off
    EXPECT_THAT(paths.pathTo(7), ElementsAre(
        matchToFrom(0, 2),
        matchToFrom(2, 7)
    ));
    // clang-format on
}

TEST_F(BellmanFordShortestPathsTest, WithNegativeCycle)
{
    auto graph = readEdgeWeightedDigraph("assets/graph/tinyEWDnc.txt");

    BellmanFordShortestPaths paths(graph, source());
    EXPECT_TRUE(paths.hasNegativeCycle());
    EXPECT_THAT(paths.negativeCycle(), ElementsAre(4, 5, 4));
}

TEST_F(BellmanFordShortestPathsTest, ArbitrageDetection)
{
    // clang-format off
    double rates[5][5] = {
    /*         USD    EUR    GBP    CHF    CAD  */
    /* USD */ {1,     0.741, 0.657, 1.061, 1.005},
    /* EUR */ {1.349, 1,     0.888, 1.433, 1.366},
    /* GBP */ {1.521, 1.126, 1,     1.614, 1.538},
    /* CHF */ {0.942, 0.698, 0.619, 1,     0.953},
    /* CAD */ {0.995, 0.732, 0.650, 1.049, 1}
    };
    // clang-format on

    EdgeWeightedDigraph graph{5};
    for (std::size_t i = 0; i < 5; ++i) {
        for (std::size_t j = 0; j < 5; ++j) {
            graph.add(DirectedEdge{i, j, -std::log(rates[i][j])});
        }
    }

    BellmanFordShortestPaths paths{graph, source()};
    EXPECT_TRUE(paths.hasNegativeCycle());
    EXPECT_THAT(paths.negativeCycle(), ElementsAre(0, 1, 4, 0) /* USD -> EUR -> CAD -> USD */);
}
