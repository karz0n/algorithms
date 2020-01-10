#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Sequence.hpp"

using namespace algorithms;

using ::testing::SizeIs;
using ::testing::Each;
using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Gt;
using ::testing::Le;
using ::testing::Lt;
using ::testing::Eq;
using ::testing::IsEmpty;

TEST(SequenceTest, IntNumbers)
{
    auto numbers = Sequence::numbers<int>(10, 1, 10);

    EXPECT_THAT(numbers, SizeIs(10));
    EXPECT_THAT(numbers, Each(AllOf((Ge(1), Le(10)))));
}

TEST(SequenceTest, FloatNumbers)
{
    auto numbers = Sequence::numbers<float>(10, 1.0, 10.0);

    EXPECT_THAT(numbers, SizeIs(10));
    EXPECT_THAT(numbers, Each(AllOf((Ge(1.0), Le(10.0)))));
}

TEST(SequenceTest, Shuffle)
{
    auto numbers = Sequence::numbers<int>(10);

    auto copy = numbers;
    Sequence::shuffle(copy.begin(), copy.end());
    EXPECT_NE(copy, numbers);
}

TEST(SequenceTest, IsAscendingPositive)
{
    Numbers<int> numbers{1, 2, 3, 4, 5};

    EXPECT_TRUE(Sequence::isAscending(numbers.cbegin(), numbers.cend()));
}

TEST(SequenceTest, IsAscendingNegative)
{
    Numbers<int> numbers{1, 3, 2, 4, 5};

    EXPECT_FALSE(Sequence::isAscending(numbers.cbegin(), numbers.cend()));
}

TEST(SequenceTest, IsAscendingForEmpty)
{
    Numbers<int> numbers{};

    EXPECT_TRUE(Sequence::isAscending(numbers.cbegin(), numbers.cend()));
}

TEST(SequenceTest, IsDescendingPositive)
{
    Numbers<int> numbers{5, 4, 3, 2, 1};

    EXPECT_TRUE(Sequence::isDescending(numbers.cbegin(), numbers.cend()));
}

TEST(SequenceTest, IsDescendingNegative)
{
    Numbers<int> numbers{5, 4, 2, 3, 1};

    EXPECT_FALSE(Sequence::isDescending(numbers.cbegin(), numbers.cend()));
}

TEST(SequenceTest, IsDescendingForEmpty)
{
    Numbers<int> numbers{};

    EXPECT_TRUE(Sequence::isDescending(numbers.cbegin(), numbers.cend()));
}

TEST(SequenceTest, PartitionSubset1)
{
    auto comparator = [](int lh, int rh) -> int {
        return (lh < rh) ? -1 : (lh > rh) ? +1 : 0;
    };

    Numbers<int> number{4 /* pivot */, 5, 3, 4, 1, 6, 4};
    auto [it1, it2] = Sequence::partition(number.begin(), number.end(), comparator);
    auto pivot = *it1;

    Numbers<int> lt(number.begin(), it1);
    Numbers<int> eq(it1, it2);
    Numbers<int> gt(it2, number.end());

    EXPECT_THAT(lt, Each(Lt(pivot)));
    EXPECT_THAT(eq, Each(Eq(pivot)));
    EXPECT_THAT(gt, Each(Gt(pivot)));
}

TEST(SequenceTest, PartitionSubset2)
{
    auto comparator = [](int lh, int rh) -> int {
        return (lh < rh) ? -1 : (lh > rh) ? +1 : 0;
    };

    Numbers<int> number{1 /* pivot */, 4, 5, 4, 3, 6, 4};
    auto [it1, it2] = Sequence::partition(number.begin(), number.end(), comparator);
    auto pivot = *it1;

    Numbers<int> lt(number.begin(), it1);
    Numbers<int> eq(it1, it2);
    Numbers<int> gt(it2, number.end());

    EXPECT_THAT(lt, IsEmpty());
    EXPECT_THAT(eq, Each(Eq(pivot)));
    EXPECT_THAT(eq, SizeIs(1));
    EXPECT_THAT(gt, Each(Gt(pivot)));
}

TEST(SequenceTest, PartitionSubset3)
{
    auto comparator = [](int lh, int rh) -> int {
        return (lh < rh) ? -1 : (lh > rh) ? +1 : 0;
    };

    Numbers<int> number{6 /* pivot */, 4, 5, 4, 3, 1, 4};
    auto [it1, it2] = Sequence::partition(number.begin(), number.end(), comparator);
    auto pivot = *it1;

    Numbers<int> lt(number.begin(), it1);
    Numbers<int> eq(it1, it2);
    Numbers<int> gt(it2, number.end());

    EXPECT_THAT(lt, Each(Lt(pivot)));
    EXPECT_THAT(eq, Each(Eq(pivot)));
    EXPECT_THAT(eq, SizeIs(1));
    EXPECT_THAT(gt, IsEmpty());
}
