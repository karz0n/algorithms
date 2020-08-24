#include <gtest/gtest.h>

#include "PriorityQueue.hpp"

using namespace algorithms;

static constexpr int MIN = 0;
static constexpr int MAX = 100;

TEST(PriorityQueue, Order)
{
    /** Max priority queue (top value is value with highest priority) */
    MaxPriorityQueue<int> queue;

    for (auto n = MIN; n <= MAX; ++n) {
        queue.push(n);
    }

    for (auto n = MAX; n >= MIN; --n) {
        ASSERT_TRUE(queue.pop() == n);
    }
}

TEST(PriorityQueue, Invariants)
{
    MaxPriorityQueue<int> queue;

    ASSERT_EQ(queue.size(), 0);
    ASSERT_TRUE(queue.empty());
    queue.push(MIN);
    queue.push(MAX);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), 2);

    ASSERT_EQ(queue.top(), MAX);
    ASSERT_EQ(queue.bottom(), MIN);

    queue.pop();
    queue.pop();

    ASSERT_EQ(queue.size(), 0);
    ASSERT_TRUE(queue.empty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(queue.pop());
#endif
}
