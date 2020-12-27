#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "AcyclicShortestPaths.hpp"

using namespace algorithms;
using namespace testing;

class AcyclicShortestPathsTest : public Test {
public:
    AcyclicShortestPathsTest()
        : graph{8}
    {
    }

    void
    SetUp() override
    {
        graph.add({0, 1, 5.0});
        graph.add({0, 4, 9.0});
        graph.add({0, 7, 8.0});
        graph.add({1, 2, 12.0});
        graph.add({1, 3, 15.0});
        graph.add({1, 7, 4.0});
        graph.add({2, 3, 3.0});
        graph.add({2, 6, 11.0});
        graph.add({3, 6, 9.0});
        graph.add({4, 5, 4.0});
        graph.add({4, 6, 20.0});
        graph.add({4, 7, 5.0});
        graph.add({5, 2, 1.0});
        graph.add({5, 6, 13.0});
        graph.add({7, 5, 6.0});
        graph.add({7, 2, 7.0});
    }

    static std::size_t
    source()
    {
        return 0;
    }

public:
    EdgeWeightedDigraph graph;
};

static Matcher<const DirectedEdge&>
matchToFrom(const std::size_t from, const std::size_t to)
{
    return AllOf(Property(&DirectedEdge::from, from), Property(&DirectedEdge::to, to));
}

TEST_F(AcyclicShortestPathsTest, ShortestPaths)
{
    AcyclicShortestPath paths{graph, source(), true};

    EXPECT_THAT(paths.distanceTo(0), DoubleEq(0.0));
    EXPECT_THAT(paths.distanceTo(1), DoubleEq(5.0));
    EXPECT_THAT(paths.distanceTo(2), DoubleEq(14.0));
    EXPECT_THAT(paths.distanceTo(3), DoubleEq(17.0));
    EXPECT_THAT(paths.distanceTo(4), DoubleEq(9.0));
    EXPECT_THAT(paths.distanceTo(5), DoubleEq(13.0));
    EXPECT_THAT(paths.distanceTo(6), DoubleEq(25.0));
    EXPECT_THAT(paths.distanceTo(7), DoubleEq(8.0));

    EXPECT_THAT(paths.edgeTo(0), Eq(std::nullopt));
    EXPECT_THAT(paths.edgeTo(1), Optional(matchToFrom(0, 1)));
    EXPECT_THAT(paths.edgeTo(2), Optional(matchToFrom(5, 2)));
    EXPECT_THAT(paths.edgeTo(3), Optional(matchToFrom(2, 3)));
    EXPECT_THAT(paths.edgeTo(4), Optional(matchToFrom(0, 4)));
    EXPECT_THAT(paths.edgeTo(5), Optional(matchToFrom(4, 5)));
    EXPECT_THAT(paths.edgeTo(6), Optional(matchToFrom(2, 6)));
    EXPECT_THAT(paths.edgeTo(7), Optional(matchToFrom(0, 7)));
}

TEST_F(AcyclicShortestPathsTest, LongestPaths)
{
    AcyclicShortestPath paths{graph, 0, false};

    EXPECT_THAT(paths.distanceTo(0), DoubleEq(0.0));
    EXPECT_THAT(paths.distanceTo(1), DoubleEq(5.0));
    EXPECT_THAT(paths.distanceTo(2), DoubleEq(21.0));
    EXPECT_THAT(paths.distanceTo(3), DoubleEq(24.0));
    EXPECT_THAT(paths.distanceTo(4), DoubleEq(9.0));
    EXPECT_THAT(paths.distanceTo(5), DoubleEq(20.0));
    EXPECT_THAT(paths.distanceTo(6), DoubleEq(33.0));
    EXPECT_THAT(paths.distanceTo(7), DoubleEq(14.0));

    EXPECT_THAT(paths.edgeTo(0), Eq(std::nullopt));
    EXPECT_THAT(paths.edgeTo(1), Optional(matchToFrom(0, 1)));
    EXPECT_THAT(paths.edgeTo(2), Optional(matchToFrom(7, 2)));
    EXPECT_THAT(paths.edgeTo(3), Optional(matchToFrom(2, 3)));
    EXPECT_THAT(paths.edgeTo(4), Optional(matchToFrom(0, 4)));
    EXPECT_THAT(paths.edgeTo(5), Optional(matchToFrom(7, 5)));
    EXPECT_THAT(paths.edgeTo(6), Optional(matchToFrom(5, 6)));
    EXPECT_THAT(paths.edgeTo(7), Optional(matchToFrom(4, 7)));
}