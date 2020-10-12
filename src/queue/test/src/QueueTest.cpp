#include <gtest/gtest.h>

#include <memory>

#include "LinkedQueue.hpp"
#include "ResizableArrayQueue.hpp"

static constexpr int MIN = 0;
static constexpr int MAX = 100;

using IntQueue = algorithms::Queue<int>;

using IntQueuePtr = std::shared_ptr<IntQueue>;

using CreateQueueFunctionPtr = IntQueuePtr (*)();

IntQueuePtr
createLinkedQueue()
{
    using IntLinkedQueue = algorithms::LinkedQueue<int>;
    return std::make_shared<IntLinkedQueue>();
}

IntQueuePtr
createResizableArrayQueue()
{
    using IntResizableArrayQueue = algorithms::ResizableArrayQueue<int>;
    return std::make_shared<IntResizableArrayQueue>();
}

class QueueTest : public ::testing::TestWithParam<CreateQueueFunctionPtr> {
public:
    void
    SetUp() override
    {
        CreateQueueFunctionPtr f = GetParam();
        _queue = f();
    }

    void
    TearDown() override
    {
        _queue.reset();
    }

protected:
    IntQueuePtr _queue;
};

TEST_P(QueueTest, Invariants)
{
    ASSERT_EQ(_queue->size(), 0);
    ASSERT_TRUE(_queue->empty());
    _queue->push(MIN);
    _queue->push(MAX);
    ASSERT_FALSE(_queue->empty());
    ASSERT_EQ(_queue->size(), 2);

    ASSERT_EQ(_queue->front(), MIN);
    ASSERT_EQ(_queue->back(), MAX);

    ASSERT_FALSE(_queue->empty());

    _queue->pop();
    _queue->pop();

    ASSERT_EQ(_queue->size(), 0);
    ASSERT_TRUE(_queue->empty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(_queue->pop());
#endif
}

TEST_P(QueueTest, Order)
{
    for (auto n = MIN; n <= MAX; ++n) {
        _queue->push(n);
    }

    for (auto n = MIN; n <= MAX; ++n) {
        ASSERT_TRUE(_queue->pop() == n);
    }
}

INSTANTIATE_TEST_SUITE_P(QueueTestSuite,
                         QueueTest,
                         ::testing::Values(&createLinkedQueue, &createResizableArrayQueue));
