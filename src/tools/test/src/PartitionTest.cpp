#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Sequence.hpp"

using namespace algorithms;

using ::testing::Each;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::Eq;

class PartitionTest : public ::testing::TestWithParam<float> {
protected:
    void
    SetUp() override
    {
        _sequence = Numbers<int>{4, 5, 3, 4, 1, 6, 4};
    }

protected:
    Numbers<int> _sequence;
};

TEST_P(PartitionTest, SequencePartition)
{
    const float MEDIAN = GetParam();

    auto comparator = [&](int v) -> int {
        return (v < MEDIAN) ? -1 : (v > MEDIAN) ? +1 : 0;
    };
    auto [it1, it2] = Sequence::partition(_sequence.begin(), _sequence.end(), comparator);

    Numbers<int> lt(_sequence.begin(), it1);
    Numbers<int> eq(it1, it2);
    Numbers<int> gt(it2, _sequence.end());

    EXPECT_THAT(lt, Each(Lt(MEDIAN)));
    EXPECT_THAT(eq, Each(Eq(MEDIAN)));
    EXPECT_THAT(gt, Each(Gt(MEDIAN)));
}

INSTANTIATE_TEST_SUITE_P(Partition,
                         PartitionTest,
                         testing::Values(2.5, 4.f, 6.f, 1.5f, 10.f));
