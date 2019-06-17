#include <gtest/gtest.h>

#include <memory>

#include "Data.hpp"
#include "OrderedMap.hpp"
#include "BinarySearchTreeMap.hpp"
#include "RedBlackBinarySearchTreeMap.hpp"

/** String data map */
using StringDataMap = algorithms::Map<std::string, Data>;

/** Pointer to string data map */
using StringDataMapPtr = std::shared_ptr<StringDataMap>;

/** Pointer to string data map factory method */
using CreateMapFunctionPtr = StringDataMapPtr (*)();

StringDataMapPtr createOrderedMap()
{
    using OrderedDataMap = algorithms::OrderedMap<std::string, Data>;
    return std::make_shared<OrderedDataMap>();
}

StringDataMapPtr createBinarySearchTreeMap()
{
    using BinarySearchTreeDataMap = algorithms::OrderedMap<std::string, Data>;
    return std::make_shared<BinarySearchTreeDataMap>();
}

StringDataMapPtr createRedBlackBinarySearchTreeMap()
{
    using RedBlackBinarySearchTreeDataMap = algorithms::OrderedMap<std::string, Data>;
    return std::make_shared<RedBlackBinarySearchTreeDataMap>();
}

class MapTest : public ::testing::TestWithParam<CreateMapFunctionPtr> {
public:
    void SetUp() override
    {
        CreateMapFunctionPtr f = *GetParam();
        _map = f();
        populate();
    }

    void TearDown() override
    {
        _map.reset();
    }

    void populate()
    {
        _map->put("S", Data{"S"});
        _map->put("E", Data{"E"});
        _map->put("A", Data{"A"});
        _map->put("C", Data{"C"});
        _map->put("X", Data{"X"});
        _map->put("R", Data{"R"});
        _map->put("H", Data{"H"});
        _map->put("M", Data{"M"});
    }

protected:
    StringDataMapPtr _map;
};

TEST_P(MapTest, EmptyTest)
{
    EXPECT_FALSE(_map->empty());
}

TEST_P(MapTest, SizeTest)
{
    EXPECT_EQ(_map->size(), 8);
}

TEST_P(MapTest, RangeSizeTest)
{
    EXPECT_EQ(_map->size("A", "H"), 4);
}

TEST_P(MapTest, ContainsTest)
{
    EXPECT_TRUE(_map->contains("E"));
}

TEST_P(MapTest, ValidGetTest)
{
    EXPECT_TRUE(_map->get("S").name == "S");
}

TEST_P(MapTest, InvalidGetTest)
{
    EXPECT_THROW(_map->get("O"), std::runtime_error);
}

TEST_P(MapTest, ValidPickTest)
{
    auto value = _map->pick("S");
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value().name, "S");
}

TEST_P(MapTest, InvalidPickTest)
{
    auto value = _map->pick("O");
    EXPECT_FALSE(value.has_value());
}

TEST_P(MapTest, MinMaxTest)
{
    EXPECT_EQ(_map->min(), "A");
    _map->eraseMin();
    EXPECT_FALSE(_map->contains("A"));

    EXPECT_EQ(_map->max(), "X");
    _map->eraseMax();
    ASSERT_FALSE(_map->contains("X"));
}

TEST_P(MapTest, EraseTest)
{
    _map->erase("C");
    EXPECT_FALSE(_map->contains("C"));
}

TEST_P(MapTest, RankTest)
{
    EXPECT_EQ(_map->rank("M"), 4);
}

TEST_P(MapTest, FloorTest)
{
    auto floorKey = _map->floor("F");
    ASSERT_TRUE(floorKey.has_value());
    EXPECT_EQ(_map->get(floorKey.value()).name, "E");
}

TEST_P(MapTest, CeilingTest)
{
    auto ceilingKey = _map->ceiling("B");
    ASSERT_TRUE(ceilingKey.has_value());
    EXPECT_EQ(_map->get(ceilingKey.value()).name, "C");
}

TEST_P(MapTest, AllKeysTest)
{
    auto keys = _map->keys();
    StringDataMap::Keys expected{"A", "C", "E", "H", "M", "R", "S", "X"};
    EXPECT_EQ(keys, expected);
}

TEST_P(MapTest, KeysTest)
{
    auto keys = _map->keys("A", "H");
    StringDataMap::Keys expected{"A", "C", "E", "H"};
    EXPECT_EQ(keys, expected);
}

INSTANTIATE_TEST_SUITE_P(MapTestMain, MapTest,
                         ::testing::Values(&createOrderedMap, &createBinarySearchTreeMap,
                                           &createRedBlackBinarySearchTreeMap));
