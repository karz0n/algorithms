#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Common.hpp"
#include "GrahamScan.hpp"

using namespace testing;
using namespace algorithms;

TEST(GrahamScanTest, Scan)
{
    Points points;
    read("assets/geometry/ConvexPoints.txt", points);
    EXPECT_THAT(points, Not(IsEmpty()));

    GrahamScan scan{points};
    const auto& hull = scan.hull();
    EXPECT_THAT(hull, Not(IsEmpty()));

    bool isConvex{true};
    const std::size_t count{hull.size()};
    for (std::size_t n{0}; n < count; ++n) {
        if (getOrientation(hull[n], hull[(n + 1) % count], hull[(n + 2) % count]) <= 0) {
            FAIL() << "Invalid orientation";
        }
    }
}