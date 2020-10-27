#include <gtest/gtest.h>

#include <ShellSort.hpp>
#include <Sequence.hpp>

using namespace testing;
using namespace algorithms;

class ShellTest : public TestWithParam<std::size_t> {
public:
    ShellTest()
        : numbers{Sequence::numbers<int>(GetParam())}
    {
    }

public:
    Numbers<int> numbers;
};

TEST_P(ShellTest, AscendingSort)
{
    ShellSort::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST_P(ShellTest, DescendingSort)
{
    ShellSort::sort(numbers.begin(), numbers.end(), std::greater<int>{});
    ASSERT_TRUE(Sequence::isDescending(numbers.begin(), numbers.end()));
}

TEST_P(ShellTest, InvalidIterators)
{
    EXPECT_NO_THROW(ShellSort::sort(numbers.end(), numbers.begin()));
}

INSTANTIATE_TEST_SUITE_P(Sort, ShellTest, Values(100, 1000, 10000));
