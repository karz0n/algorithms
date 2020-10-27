#include <gtest/gtest.h>

#include <InsertionSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class InsertionTest : public TestWithParam<std::size_t> {
public:
    InsertionTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(InsertionTest, AscendingSort)
{
    InsertionSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(InsertionTest, DescendingSort)
{
    InsertionSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(InsertionTest, InvalidIterators)
{
    EXPECT_NO_THROW(InsertionSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, InsertionTest, Values(100, 1000, 10000));
