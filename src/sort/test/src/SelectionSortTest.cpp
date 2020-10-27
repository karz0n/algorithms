#include <gtest/gtest.h>

#include <SelectionSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class SelectionTest : public TestWithParam<std::size_t> {
public:
    SelectionTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(SelectionTest, AscendingSort)
{
    SelectionSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(SelectionTest, DescendingSort)
{
    SelectionSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(SelectionTest, InvalidIterators)
{
    EXPECT_NO_THROW(SelectionSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, SelectionTest, Values(100, 1000, 10000));
