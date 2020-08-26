#include <gtest/gtest.h>

#include "BinaryTree.hpp"
#include "RedBlackTree.hpp"

#include <string>
#include <vector>

using namespace algorithms;

static const std::vector<std::string> TEST_DATA{"P", "H", "D", "B", "A", "C", "F", "E", "G",
                                                "L", "J", "I", "K", "N", "M", "O", "T", "R",
                                                "Q", "S", "X", "V", "U", "W", "Z", "Y"};

template<typename T>
class TreeTest : public ::testing::Test {
protected:
    void
    SetUp() override
    {
        fillByTestData();
    }

protected:
    void
    fillByTestData()
    {
        std::for_each(TEST_DATA.cbegin(), TEST_DATA.cend(),
                      [&](const auto& d) { _tree.put(d, d); });
    }

protected:
    T _tree;
};

using BinaryStringTree = BinaryTree<std::string, std::string>;
using RedBlackStringTree = RedBlackTree<std::string, std::string>;

using TestTypes = ::testing::Types<BinaryStringTree, RedBlackStringTree>;
TYPED_TEST_SUITE(TreeTest, TestTypes);

TYPED_TEST(TreeTest, EmptyTest)
{
    EXPECT_FALSE(this->_tree.empty());
}

TYPED_TEST(TreeTest, SizeTest)
{
    EXPECT_EQ(this->_tree.size(), TEST_DATA.size());
}

TYPED_TEST(TreeTest, RangeSizeTest)
{
    EXPECT_EQ(this->_tree.size("A", "H"), 8);
}

TYPED_TEST(TreeTest, ContainsTest)
{
    EXPECT_TRUE(this->_tree.contains("E"));
}

TYPED_TEST(TreeTest, ValidGetTest)
{
    EXPECT_EQ(this->_tree.get("S"), "S");
}

TYPED_TEST(TreeTest, InvalidGetTest)
{
    EXPECT_THROW(this->_tree.get("o"), std::runtime_error);
}

TYPED_TEST(TreeTest, ValidPickTest)
{
    auto value = this->_tree.pick("S");
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), "S");
}

TYPED_TEST(TreeTest, PickTest)
{
    auto value = this->_tree.pick("o");
    EXPECT_FALSE(value.has_value());
}

TYPED_TEST(TreeTest, MinTest)
{
    EXPECT_EQ(this->_tree.min(), "A");
    this->_tree.eraseMin();
    EXPECT_FALSE(this->_tree.contains("A"));
}

TYPED_TEST(TreeTest, MaxTest)
{
    EXPECT_EQ(this->_tree.max(), "Z");
    this->_tree.eraseMax();
    ASSERT_FALSE(this->_tree.contains("Z"));
}

TYPED_TEST(TreeTest, EraseTest)
{
    this->_tree.erase("R");
    EXPECT_FALSE(this->_tree.contains("R"));
}

TYPED_TEST(TreeTest, RankTest)
{
    EXPECT_EQ(this->_tree.rank("M"), 12);
}

TYPED_TEST(TreeTest, FloorTest)
{
    this->_tree.erase("F");
    auto key = this->_tree.floor("F");
    ASSERT_TRUE(key.has_value());
    EXPECT_EQ(this->_tree.get(key.value()), "E");
}

TYPED_TEST(TreeTest, CeilingTest)
{
    this->_tree.erase("B");
    auto key = this->_tree.ceiling("B");
    ASSERT_TRUE(key.has_value());
    EXPECT_EQ(this->_tree.get(key.value()), "C");
}

TYPED_TEST(TreeTest, AllKeysTest)
{
    static const typename TypeParam::KeysType EXPECTED{"A", "B", "C", "D", "E", "F", "G", "H", "I",
                                                       "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                                                       "S", "T", "U", "V", "W", "X", "Y", "Z"};

    auto keys = this->_tree.keys();

    EXPECT_EQ(keys, EXPECTED);
}

TYPED_TEST(TreeTest, KeysTest)
{
    auto keys = this->_tree.keys("A", "H");
    typename TypeParam::KeysType expected{"A", "B", "C", "D", "E", "F", "G", "H"};
    EXPECT_EQ(keys, expected);
}

TYPED_TEST(TreeTest, DepthPreOrderTraverseTest)
{
    static const typename TypeParam::KeysType EXPECTED(TEST_DATA.cbegin(), TEST_DATA.cend());

    typename TypeParam::KeysType keys;
    this->_tree.traverse(
        TraverseOrder::DepthPreOrder, [&keys](const auto& key, auto&) { keys.push_back(key); },
        true);
    EXPECT_EQ(keys, EXPECTED);

    keys.clear();
    this->_tree.traverse(
        TraverseOrder::DepthPreOrder, [&keys](const auto& key, auto&) { keys.push_back(key); },
        false);
    EXPECT_EQ(keys, EXPECTED);
}

TYPED_TEST(TreeTest, DepthInOrderTraverseTest)
{
    static const typename TypeParam::KeysType EXPECTED{"A", "B", "C", "D", "E", "F", "G", "H", "I",
                                                       "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                                                       "S", "T", "U", "V", "W", "X", "Y", "Z"};

    typename TypeParam::KeysType keys;
    this->_tree.traverse(
        TraverseOrder::DepthInOrder, [&keys](const auto& key, auto&) { keys.push_back(key); },
        true);
    EXPECT_EQ(keys, EXPECTED);

    keys.clear();
    this->_tree.traverse(
        TraverseOrder::DepthInOrder, [&keys](const auto& key, auto&) { keys.push_back(key); },
        false);
    EXPECT_EQ(keys, EXPECTED);
}

TYPED_TEST(TreeTest, DepthPostOrderTraverseTest)
{
    static const typename TypeParam::KeysType EXPECTED{"A", "C", "B", "E", "G", "F", "D", "I", "K",
                                                       "J", "M", "O", "N", "L", "H", "Q", "S", "R",
                                                       "U", "W", "V", "Y", "Z", "X", "T", "P"};

    typename TypeParam::KeysType keys;
    this->_tree.traverse(
        TraverseOrder::DepthPostOrder, [&keys](const auto& key, auto&) { keys.push_back(key); },
        true);
    EXPECT_EQ(keys, EXPECTED);

    keys.clear();
    this->_tree.traverse(
        TraverseOrder::DepthPostOrder, [&keys](const auto& key, auto&) { keys.push_back(key); },
        false);
    EXPECT_EQ(keys, EXPECTED);
}

TYPED_TEST(TreeTest, BreadthOrderTraverseTest)
{
    static const typename TypeParam::KeysType EXPECTED{"P", "H", "T", "D", "L", "R", "X", "B", "F",
                                                       "J", "N", "Q", "S", "V", "Z", "A", "C", "E",
                                                       "G", "I", "K", "M", "O", "U", "W", "Y"};

    typename TypeParam::KeysType keys;
    this->_tree.traverse(TraverseOrder::BreadthOrder,
                         [&](const auto& key, auto&) { keys.push_back(key); });

    EXPECT_EQ(keys, EXPECTED);
}
