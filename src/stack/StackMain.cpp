#include <gtest/gtest.h>

#include "FixedArrayStack.hpp"
#include "LinkedStack.hpp"
#include "ResizableArrayStack.hpp"

using namespace algorithms;

TEST(Stack, LinkedStack)
{
    LinkedStack<int> stack;

    ASSERT_TRUE(stack.isEmpty());

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    ASSERT_FALSE(stack.isEmpty());

    ASSERT_TRUE(stack.pop() == 5);
    ASSERT_TRUE(stack.pop() == 4);
    ASSERT_TRUE(stack.pop() == 3);
    ASSERT_TRUE(stack.pop() == 2);
    ASSERT_TRUE(stack.pop() == 1);

    ASSERT_TRUE(stack.isEmpty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(stack.pop());
#endif
}

TEST(Stack, FixedArrayStack)
{
    FixedArrayStack<int> stack(5);

    ASSERT_TRUE(stack.isEmpty());

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

#ifndef NDEBUG
    ASSERT_ANY_THROW(stack.push(6));
#endif

    ASSERT_FALSE(stack.isEmpty());

    ASSERT_TRUE(stack.pop() == 5);
    ASSERT_TRUE(stack.pop() == 4);
    ASSERT_TRUE(stack.pop() == 3);
    ASSERT_TRUE(stack.pop() == 2);
    ASSERT_TRUE(stack.pop() == 1);

    ASSERT_TRUE(stack.isEmpty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(stack.pop());
#endif
}

TEST(Stack, ResizableArrayStack)
{
    ResizableArrayStack<int> stack;

    ASSERT_TRUE(stack.isEmpty());

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    ASSERT_FALSE(stack.isEmpty());

    ASSERT_TRUE(stack.pop() == 5);
    ASSERT_TRUE(stack.pop() == 4);
    ASSERT_TRUE(stack.pop() == 3);
    ASSERT_TRUE(stack.pop() == 2);
    ASSERT_TRUE(stack.pop() == 1);

    ASSERT_TRUE(stack.isEmpty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(stack.pop());
#endif
}
