#include <gtest/gtest.h>

#include <MergeSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class MergeTest : public TestWithParam<std::size_t> {
public:
    MergeTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(MergeTest, AscendingSort)
{
    MergeSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(MergeTest, DescendingSort)
{
    MergeSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(MergeTest, InvalidIterators)
{
    EXPECT_NO_THROW(MergeSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, MergeTest, Values(100, 1000, 10000));
