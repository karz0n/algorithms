#include <gtest/gtest.h>

#include <BottomUpMergeSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class BottomUpMergeTest : public TestWithParam<std::size_t> {
public:
    BottomUpMergeTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(BottomUpMergeTest, AscendingSort)
{
    BottomUpMergeSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(BottomUpMergeTest, DescendingSort)
{
    BottomUpMergeSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(BottomUpMergeTest, InvalidIterators)
{
    EXPECT_NO_THROW(BottomUpMergeSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, BottomUpMergeTest, Values(100, 1000, 10000));
