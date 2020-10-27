#include <gtest/gtest.h>

#include <HeapSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class HeapSortTest : public TestWithParam<std::size_t> {
public:
    HeapSortTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(HeapSortTest, AscendingSort)
{
    HeapSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(HeapSortTest, DescendingSort)
{
    HeapSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(HeapSortTest, InvalidIterators)
{
    EXPECT_NO_THROW(HeapSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, HeapSortTest, Values(100, 1000, 10000));
