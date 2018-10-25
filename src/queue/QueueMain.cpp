#include <gtest/gtest.h>

#include "LinkedQueue.hpp"
#include "ResizableArrayQueue.hpp"

using namespace algorithms;

TEST(Queue, LinkedQueue)
{
    LinkedQueue<int> queue;

    ASSERT_TRUE(queue.isEmpty());

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);

    ASSERT_FALSE(queue.isEmpty());

    ASSERT_TRUE(queue.dequeue() == 1);
    ASSERT_TRUE(queue.dequeue() == 2);
    ASSERT_TRUE(queue.dequeue() == 3);
    ASSERT_TRUE(queue.dequeue() == 4);
    ASSERT_TRUE(queue.dequeue() == 5);

    ASSERT_TRUE(queue.isEmpty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(queue.dequeue());
#endif
}

TEST(Queue, ResizableArrayQueue)
{
    ResizableArrayQueue<int> queue;

    ASSERT_TRUE(queue.isEmpty());

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);

    ASSERT_FALSE(queue.isEmpty());

    ASSERT_TRUE(queue.dequeue() == 1);
    ASSERT_TRUE(queue.dequeue() == 2);
    ASSERT_TRUE(queue.dequeue() == 3);
    ASSERT_TRUE(queue.dequeue() == 4);
    ASSERT_TRUE(queue.dequeue() == 5);

    ASSERT_TRUE(queue.isEmpty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(queue.dequeue());
#endif
}
