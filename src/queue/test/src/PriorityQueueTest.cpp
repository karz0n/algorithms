#include "PriorityQueue.hpp"

#include <gtest/gtest.h>

using namespace algorithms;

static constexpr int MinValue = 0;
static constexpr int MaxValue = 9;

TEST(PriorityQueue, Order)
{
    MaxPriorityQueue<int> queue;

    for (auto n = MinValue; n <= MaxValue; ++n) {
        queue.push(n);
    }

    for (auto n = MaxValue; n >= MinValue; --n) {
        ASSERT_TRUE(queue.pop() == n);
    }
}

TEST(PriorityQueue, Invariants)
{
    MaxPriorityQueue<int> queue;

    ASSERT_EQ(queue.size(), 0);
    ASSERT_TRUE(queue.empty());
    queue.push(MinValue);
    queue.push(MaxValue);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 2);

    ASSERT_EQ(queue.top(), MaxValue);
    ASSERT_EQ(queue.bottom(), MinValue);

    queue.pop();
    queue.pop();

    ASSERT_EQ(queue.size(), 0);
    ASSERT_TRUE(queue.empty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(queue.pop());
#endif
}
