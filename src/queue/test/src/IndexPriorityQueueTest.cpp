#include "IndexPriorityQueue.hpp"

#include <gtest/gtest.h>

using namespace algorithms;

static constexpr int MinValue = 0;
static constexpr int MaxValue = 9;

TEST(IndexPriorityQueueTest, Order)
{
    IndexMaxPriorityQueue<int> queue{MaxValue - MinValue + 1};

    for (auto n = MinValue; n <= MaxValue; ++n) {
        queue.push(n, n);
    }

    for (auto n = MaxValue; n >= MinValue; --n) {
        EXPECT_EQ(queue.topKey(), n);
        [[maybe_unused]] auto index = queue.pop();
    }
}

TEST(IndexPriorityQueueTest, Invariants)
{
    IndexMaxPriorityQueue<int> queue{MaxValue - MinValue + 1};

    ASSERT_EQ(queue.size(), 0);
    ASSERT_TRUE(queue.empty());
    queue.push(MinValue, MaxValue);
    queue.push(MaxValue, MinValue);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 2);

    EXPECT_EQ(queue.topKey(), MaxValue);
    EXPECT_EQ(queue.topIndex(), MinValue);

    EXPECT_EQ(queue.pop(), MinValue);
    EXPECT_EQ(queue.pop(), MaxValue);

    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.empty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(queue.pop());
#endif
}