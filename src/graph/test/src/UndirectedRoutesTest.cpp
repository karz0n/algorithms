#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"

#include <UndirectedGraph.hpp>
#include <BreadthFirstRoutes.hpp>
#include <DepthFirstRoutes.hpp>

using namespace algorithms;

using ::testing::SizeIs;
using ::testing::Ge;
using ::testing::Contains;
using ::testing::AllOf;

template<typename T>
class UndirectedRoutesTest : public ::testing::Test {
protected:
    void
    SetUp() override
    {
        read("assets/graph/tinyG.txt", graph);
    }

protected:
    UndirectedGraph graph;
};

using TestTypes = ::testing::Types<DepthFirstRoutes, BreadthFirstRoutes>;
TYPED_TEST_SUITE(UndirectedRoutesTest, TestTypes);

TYPED_TEST(UndirectedRoutesTest, HasRouteTo)
{
    TypeParam r1{this->graph, 0};
    EXPECT_TRUE(r1.hasRouteTo(4));
    EXPECT_FALSE(r1.hasRouteTo(11));

    TypeParam r2{this->graph, 9};
    EXPECT_TRUE(r2.hasRouteTo(11));
    EXPECT_FALSE(r2.hasRouteTo(4));
}

TYPED_TEST(UndirectedRoutesTest, RouteTo)
{
    TypeParam r1{this->graph, 0};
    auto route = r1.routeTo(4);
    EXPECT_THAT(route, SizeIs(Ge(2)));
    EXPECT_THAT(route, AllOf(Contains(0), Contains(4)));

    TypeParam r2{this->graph, 9};
    route = r2.routeTo(11);
    EXPECT_THAT(route, SizeIs(Ge(2)));
    EXPECT_THAT(route, AllOf(Contains(9), Contains(11)));
}
