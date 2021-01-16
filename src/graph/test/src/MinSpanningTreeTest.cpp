#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "UnionFind.hpp"
#include "PrimsMinSpanningTree.hpp"
#include "KruskalMinSpanningTree.hpp"

using namespace testing;
using namespace algorithms;

template<typename T>
class MinSpanningTreeTest : public Test {
public:
    bool
    containsCycle(const algorithms::EdgeWeightedGraph& graph, const Edges& minSpanningTree)
    {
        UnionFind unions{graph.verticesCount()};
        for (const auto& edge : minSpanningTree) {
            const std::size_t v{edge.either()};
            const std::size_t w{edge.other(v)};
            if (unions.find(v) == unions.find(w)) {
                return true;
            }
            unions.associate(v, w);
        }
        return false;
    }

    bool
    isFullCoverage(const algorithms::EdgeWeightedGraph& graph, const Edges& minSpanningTree)
    {
        UnionFind unions{graph.verticesCount()};
        for (const auto& edge : minSpanningTree) {
            const std::size_t v{edge.either()};
            const std::size_t w{edge.other(v)};
            unions.associate(v, w);
        }

        for (const auto& edge : graph.edges()) {
            const std::size_t v{edge.either()};
            const std::size_t w{edge.other(v)};
            if (unions.find(v) != unions.find(w)) {
                return false;
            }
        }

        return true;
    }

    bool
    isMinSpanningTree(const algorithms::EdgeWeightedGraph& graph, const Edges& minSpanningTree)
    {
        for (const auto edgeS : minSpanningTree) {
            UnionFind unions{graph.verticesCount()};
            for (const auto edge : minSpanningTree) {
                if (edge != edgeS) {
                    const std::size_t v{edge.either()};
                    const std::size_t w{edge.other(v)};
                    unions.associate(v, w);
                }
            }

            for (const auto edgeG : graph.edges()) {
                const std::size_t v{edgeG.either()};
                const std::size_t w{edgeG.other(v)};
                if (unions.find(v) != unions.find(w)) {
                    if (edgeS.weight() > edgeG.weight()) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};

using Implementations = Types<PrimsMinSpanningTree, KruskalMinSpanningTree>;
TYPED_TEST_SUITE(MinSpanningTreeTest, Implementations);

TYPED_TEST(MinSpanningTreeTest, tinyGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ read("assets/graph/tinyEWG.txt", graph); });

    TypeParam tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(10.46351));

    EXPECT_FALSE(this->containsCycle(graph, tree.edges()));
    EXPECT_TRUE(this->isFullCoverage(graph, tree.edges()));
    EXPECT_TRUE(this->isMinSpanningTree(graph, tree.edges()));
}

TYPED_TEST(MinSpanningTreeTest, mediumGraph)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ read("assets/graph/mediumEWG.txt", graph); });

    TypeParam tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(20.7732));

    EXPECT_FALSE(this->containsCycle(graph, tree.edges()));
    EXPECT_TRUE(this->isFullCoverage(graph, tree.edges()));
    EXPECT_TRUE(this->isMinSpanningTree(graph, tree.edges()));
}

TYPED_TEST(MinSpanningTreeTest, DISABLED_largeGraph /* Disabled due takes too much time */)
{
    EdgeWeightedGraph graph;
    ASSERT_NO_THROW({ read("assets/graph/largeEWG.txt", graph); });

    TypeParam tree{graph};
    EXPECT_THAT(tree.edges(), Not(IsEmpty()));
    EXPECT_THAT(tree.weight(), DoubleEq(65.2407));

    EXPECT_FALSE(this->containsCycle(graph, tree.edges()));
    EXPECT_TRUE(this->isFullCoverage(graph, tree.edges()));
    EXPECT_TRUE(this->isMinSpanningTree(graph, tree.edges()));
}