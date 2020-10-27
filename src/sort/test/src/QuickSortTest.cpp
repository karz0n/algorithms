#include <gtest/gtest.h>

#include <QuickSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class QuickTest : public TestWithParam<std::size_t> {
public:
    QuickTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(QuickTest, AscendingSort)
{
    QuickSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(QuickTest, DescendingSort)
{
    QuickSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(QuickTest, InvalidIterators)
{
    EXPECT_NO_THROW(QuickSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, QuickTest, Values(100, 1000, 10000));
