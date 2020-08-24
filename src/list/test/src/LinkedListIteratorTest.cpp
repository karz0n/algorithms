#include <gtest/gtest.h>

#include "LinkedList.hpp"

using namespace algorithms;

static constexpr int MIN = 0;
static constexpr int MAX = 50;

TEST(LinkedListIterator, Iteration)
{
    LinkedList<int> list;

    for (auto n = MIN; n <= MAX; ++n) {
        list.pushBack(n);
    }

    auto it = list.begin();
    for (auto n = MIN; n <= MAX; ++n) {
        ASSERT_EQ(*it, n);
        it++;
    }
}

TEST(LinkedListIterator, ManualIteration)
{
    LinkedList<int> list;

    int c = 5;
    while (c--) {
        list.pushFront(c);
    }

    auto it = list.begin();
    int v = it++;
    ASSERT_TRUE(v == 0);
    v = it++;
    ASSERT_TRUE(v == 1);
    v = it++;
    ASSERT_TRUE(v == 2);
    v = it++;
    ASSERT_TRUE(v == 3);
    v = it--;
    ASSERT_TRUE(v == 4);
    v = it--;
    ASSERT_TRUE(v == 3);
    v = it--;
    ASSERT_TRUE(v == 2);
    v = it--;
    ASSERT_TRUE(v == 1);
    v = it--;
    ASSERT_TRUE(v == 0);
}
