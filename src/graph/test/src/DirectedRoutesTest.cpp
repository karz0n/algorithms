#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"

#include <DirectedGraph.hpp>
#include <BreadthFirstRoutes.hpp>
#include <DepthFirstRoutes.hpp>

using namespace algorithms;

using ::testing::SizeIs;
using ::testing::Ge;
using ::testing::Eq;
using ::testing::Contains;
using ::testing::AllOf;
using ::testing::AnyOf;

template<typename T>
class DirectedRoutesTest : public ::testing::Test {
protected:
    void
    SetUp() override
    {
        readGraph("assets/graph/tinyG.txt", graph);
    }

protected:
    DirectedGraph graph;
};

using TestTypes = ::testing::Types<DepthFirstRoutes, BreadthFirstRoutes>;
TYPED_TEST_SUITE(DirectedRoutesTest, TestTypes);

TYPED_TEST(DirectedRoutesTest, HasRouteTo)
{
    TypeParam r1{this->graph, 0};
    EXPECT_TRUE(r1.hasRouteTo(4));
    EXPECT_FALSE(r1.hasRouteTo(11));

    TypeParam r2{this->graph, 9};
    EXPECT_TRUE(r2.hasRouteTo(11));
    EXPECT_FALSE(r2.hasRouteTo(4));
}

TYPED_TEST(DirectedRoutesTest, RouteTo)
{
    TypeParam r1{this->graph, 0};
    auto route = r1.routeTo(4);
    EXPECT_THAT(route, SizeIs(Ge(2)));
    EXPECT_THAT(route, AllOf(Contains(0), AnyOf(Contains(5), Contains(6)), Contains(4)));

    TypeParam r2{this->graph, 9};
    route = r2.routeTo(11);
    EXPECT_THAT(route, SizeIs(Eq(2)));
    EXPECT_THAT(route, AllOf(Contains(9), Contains(11)));
}
