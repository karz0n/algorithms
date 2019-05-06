#include <gtest/gtest.h>

#include "Data.hpp"
#include "BinarySearchTreeMap.hpp"

using namespace algorithms;

class BinarySearchTreeMapTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        map.put("S", Data{"S"});
        map.put("E", Data{"E"});
        map.put("A", Data{"A"});
        map.put("C", Data{"C"});
        map.put("X", Data{"X"});
        map.put("R", Data{"R"});
        map.put("H", Data{"H"});
        map.put("M", Data{"M"});
    }

    void TearDown() override
    {
    }

protected:
    BinarySearchTreeMap<std::string, Data> map;
};

TEST_F(BinarySearchTreeMapTest, EmptyTest)
{
    EXPECT_FALSE(map.empty());
}

TEST_F(BinarySearchTreeMapTest, SizeTest)
{
    EXPECT_EQ(map.size(), 8);
}

TEST_F(BinarySearchTreeMapTest, ContainsTest)
{
    EXPECT_TRUE(map.contains("E"));
}

TEST_F(BinarySearchTreeMapTest, ValidGetTest)
{
    EXPECT_TRUE(map.get("S").name == "S");
}

TEST_F(BinarySearchTreeMapTest, InvalidGetTest)
{
    EXPECT_THROW(map.get("O"), std::runtime_error);
}

TEST_F(BinarySearchTreeMapTest, ValidPickTest)
{
    auto value = map.pick("S");
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value().name, "S");
}

TEST_F(BinarySearchTreeMapTest, InvalidPickTest)
{
    auto value = map.pick("O");
    EXPECT_FALSE(value.has_value());
}

TEST_F(BinarySearchTreeMapTest, MinMaxTest)
{
    auto minKey = map.min();
    ASSERT_TRUE(minKey.has_value());
    EXPECT_EQ(map.get(minKey.value()).name, "A");
    map.eraseMin();
    EXPECT_FALSE(map.contains("A"));

    auto maxKey = map.max();
    ASSERT_TRUE(maxKey.has_value());
    EXPECT_EQ(map.get(maxKey.value()).name, "X");
    map.eraseMax();
    ASSERT_FALSE(map.contains("X"));
}

TEST_F(BinarySearchTreeMapTest, EraseTest)
{
    map.erase("C");
    EXPECT_FALSE(map.contains("C"));
}

TEST_F(BinarySearchTreeMapTest, RankTest)
{
    EXPECT_EQ(map.rank("M"), 4);
}

TEST_F(BinarySearchTreeMapTest, FloorTest)
{
    auto floorKey = map.floor("F");
    ASSERT_TRUE(floorKey.has_value());
    EXPECT_EQ(map.get(floorKey.value()).name, "E");
}

TEST_F(BinarySearchTreeMapTest, CeilingTest)
{
    auto ceilingKey = map.ceiling("B");
    ASSERT_TRUE(ceilingKey.has_value());
    EXPECT_EQ(map.get(ceilingKey.value()).name, "C");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
