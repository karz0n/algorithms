#include <gtest/gtest.h>

#include "PriorityQueue.hpp"

using namespace algorithms;

TEST(Queue, MaxPriorityQueue)
{
    /** Max priority queue (top value is value with highest priority) */
    MaxPriorityQueue<int> queue;

    ASSERT_TRUE(queue.empty());

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);

    ASSERT_FALSE(queue.empty());

    ASSERT_TRUE(queue.dequeue() == 5);
    ASSERT_TRUE(queue.dequeue() == 4);
    ASSERT_TRUE(queue.dequeue() == 3);
    ASSERT_TRUE(queue.dequeue() == 2);
    ASSERT_TRUE(queue.dequeue() == 1);

    ASSERT_TRUE(queue.empty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(queue.dequeue());
#endif
}

TEST(Queue, MinPriorityQueue)
{
    /** Min priority queue (top value is value with lowest priority)  */
    MinPriorityQueue<int> queue;

    ASSERT_TRUE(queue.empty());

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);

    ASSERT_FALSE(queue.empty());

    ASSERT_TRUE(queue.dequeue() == 1);
    ASSERT_TRUE(queue.dequeue() == 2);
    ASSERT_TRUE(queue.dequeue() == 3);
    ASSERT_TRUE(queue.dequeue() == 4);
    ASSERT_TRUE(queue.dequeue() == 5);

    ASSERT_TRUE(queue.empty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(queue.dequeue());
#endif
}
