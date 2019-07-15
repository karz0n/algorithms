#include <gtest/gtest.h>

#include "LinkedList.hpp"

using namespace algorithms;

static constexpr int MIN = 0;
static constexpr int MAX = 50;

TEST(LinkedList, PushFront)
{
    LinkedList<int> list;

    for (auto n = MIN; n <= MAX; ++n) {
        list.pushFront(n);
    }

    ASSERT_EQ(list.front(), MAX);

    for (auto n = MAX; n >= MIN; --n) {
        ASSERT_TRUE(list.popFront() == n);
    }
}

TEST(LinkedList, PushBack)
{
    LinkedList<int> list;

    for (auto n = MIN; n <= MAX; ++n) {
        list.pushBack(n);
    }

    ASSERT_EQ(list.back(), MAX);

    for (auto n = MAX; n >= MIN; --n) {
        ASSERT_TRUE(list.popBack() == n);
    }
}

TEST(LinkedList, Invariants)
{
    LinkedList<int> list;

    ASSERT_TRUE(list.empty());

    list.pushBack(MIN);
    list.pushBack(MAX);

    ASSERT_FALSE(list.empty());

    ASSERT_EQ(list.front(), MIN);
    ASSERT_EQ(list.back(), MAX);

    list.popFront();
    list.popFront();

    ASSERT_TRUE(list.empty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(list.popFront());
    ASSERT_ANY_THROW(list.popBack());
#endif
}
