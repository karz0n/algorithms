#include <gtest/gtest.h>

#include <ThreeWayQuickSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class ThreeWayQuickTest : public TestWithParam<std::size_t> {
public:
    ThreeWayQuickTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(ThreeWayQuickTest, AscendingSort)
{
    ThreeWayQuickSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(ThreeWayQuickTest, DescendingSort)
{
    ThreeWayQuickSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(ThreeWayQuickTest, InvalidIterators)
{
    EXPECT_NO_THROW(ThreeWayQuickSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, ThreeWayQuickTest, Values(100, 1000, 10000));