#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LinkedList.hpp"

using namespace algorithms;

TEST(List, LinkedList)
{
    LinkedList<int> list;

    ASSERT_TRUE(list.isEmpty());

#ifndef NDEBUG
    ASSERT_ANY_THROW(list.popFront());
    ASSERT_ANY_THROW(list.popBack());
#endif

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);

    list.pushFront(-1);
    list.pushFront(-2);
    list.pushFront(-3);

    ASSERT_FALSE(list.isEmpty());

    ASSERT_TRUE(list.popFront() == -3);
    ASSERT_TRUE(list.popFront() == -2);
    ASSERT_TRUE(list.popFront() == -1);

    ASSERT_TRUE(list.popBack() == 3);
    ASSERT_TRUE(list.popBack() == 2);
    ASSERT_TRUE(list.popBack() == 1);

    ASSERT_TRUE(list.isEmpty());
}

TEST(List, LinkedListIterator)
{
    LinkedList<int> list;

    std::size_t c = 5;
    while (c--) {
        list.pushFront(c);
    }

    auto it1 = list.begin();
    int v = it1++;
    ASSERT_TRUE(v == 0);
    v = it1++;
    ASSERT_TRUE(v == 1);
    v = it1++;
    ASSERT_TRUE(v == 2);
    v = it1++;
    ASSERT_TRUE(v == 3);
    v = it1--;
    ASSERT_TRUE(v == 4);
    v = it1--;
    ASSERT_TRUE(v == 3);
    v = it1--;
    ASSERT_TRUE(v == 2);
    v = it1--;
    ASSERT_TRUE(v == 1);
    v = it1--;
    ASSERT_TRUE(v == 0);

    std::vector<int> values;
    for (auto it2 = list.begin(); it2 != list.end(); ++it2) {
        values.push_back(*it2);
    }

    std::vector<int> expected{0,1,2,3,4};
    ASSERT_THAT(values, expected);
}
