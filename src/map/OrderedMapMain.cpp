#include <gtest/gtest.h>

#include "OrderedMap.hpp"

using namespace algorithms;

TEST(Map, OrderedMap)
{
    OrderedMap<int, std::string> map;

    ASSERT_TRUE(map.empty());

    map.put(1, "1");
    map.put(3, "3");
    map.put(5, "5");
    map.put(7, "7");
    map.put(9, "9");

    ASSERT_FALSE(map.empty());

    ASSERT_TRUE(map.contains(1));
    ASSERT_TRUE(map.contains(3));
    ASSERT_TRUE(map.contains(5));
    ASSERT_TRUE(map.contains(7));
    ASSERT_TRUE(map.contains(9));

    auto v = map.get(1);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(v.value(), "1");

    v = map.get(3);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(map.get(3).value(), "3");

    v = map.get(5);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(map.get(5).value(), "5");

    v = map.get(7);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(map.get(7).value(), "7");

    v = map.get(9);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(map.get(9).value(), "9");

    auto k = map.floor(6);
    ASSERT_TRUE(k.has_value());
    ASSERT_EQ(k.value(), 5);

    k = map.ceiling(6);
    ASSERT_TRUE(k.has_value());
    ASSERT_EQ(k.value(), 7);

    k = map.min();
    ASSERT_TRUE(k.has_value());
    ASSERT_EQ(k.value(), 1);

    k = map.max();
    ASSERT_TRUE(k.has_value());
    ASSERT_EQ(k.value(), 9);

    auto keys = map.keys(2, 8);
    ASSERT_EQ(keys, std::vector({3, 5, 7}));

    auto sz = map.size(2, 8);
    ASSERT_EQ(sz, 3);
}
