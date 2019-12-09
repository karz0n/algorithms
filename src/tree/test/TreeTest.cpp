#include <gtest/gtest.h>

#include "TreeTestData.hpp"

/** Pointer to string data tree factory method */
using CreateTestFileDataTreeFunctionPtr = TestFileDataTreePtr (*)();

class TreeTest : public ::testing::TestWithParam<CreateTestFileDataTreeFunctionPtr> {
public:
    void
    SetUp()
    {
        CreateTestFileDataTreeFunctionPtr f = *GetParam();
        _tree = f();
    }

protected:
    TestFileDataTreePtr _tree;
};

TEST_P(TreeTest, EmptyTest)
{
    EXPECT_FALSE(_tree->empty());
}

TEST_P(TreeTest, SizeTest)
{
    EXPECT_EQ(_tree->size(), TEST_DATA_SIZE);
}

TEST_P(TreeTest, RangeSizeTest)
{
    EXPECT_EQ(_tree->size("A", "H"), 8);
}

TEST_P(TreeTest, ContainsTest)
{
    EXPECT_TRUE(_tree->contains("E"));
}

TEST_P(TreeTest, ValidGetTest)
{
    EXPECT_EQ(_tree->get("S"), "S");
}

TEST_P(TreeTest, InvalidGetTest)
{
    EXPECT_THROW(_tree->get("o"), std::runtime_error);
}

TEST_P(TreeTest, ValidPickTest)
{
    auto value = _tree->pick("S");
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), "S");
}

TEST_P(TreeTest, PickTest)
{
    auto value = _tree->pick("o");
    EXPECT_FALSE(value.has_value());
}

TEST_P(TreeTest, MinTest)
{
    EXPECT_EQ(_tree->min(), "A");
    _tree->eraseMin();
    EXPECT_FALSE(_tree->contains("A"));
}

TEST_P(TreeTest, MaxTest)
{
    EXPECT_EQ(_tree->max(), "Z");
    _tree->eraseMax();
    ASSERT_FALSE(_tree->contains("Z"));
}

TEST_P(TreeTest, EraseTest)
{
    _tree->erase("R");
    EXPECT_FALSE(_tree->contains("R"));
}

TEST_P(TreeTest, RankTest)
{
    EXPECT_EQ(_tree->rank("M"), 12);
}

TEST_P(TreeTest, FloorTest)
{
    _tree->erase("F");
    auto key = _tree->floor("F");
    ASSERT_TRUE(key.has_value());
    EXPECT_EQ(_tree->get(key.value()), "E");
}

TEST_P(TreeTest, CeilingTest)
{
    _tree->erase("B");
    auto key = _tree->ceiling("B");
    ASSERT_TRUE(key.has_value());
    EXPECT_EQ(_tree->get(key.value()), "C");
}

TEST_P(TreeTest, AllKeysTest)
{
    static const DataTree::KeysType EXPECTED{
        "A", "B", "C", "D", "E", "F", "G",
        "H", "I", "J", "K", "L", "M", "N",
        "O", "P", "Q", "R", "S", "T", "U",
        "V", "W", "X", "Y", "Z"};

    auto keys = _tree->keys();

    EXPECT_EQ(keys, EXPECTED);
}

TEST_P(TreeTest, KeysTest)
{
    auto keys = _tree->keys("A", "H");
    DataTree::KeysType expected{"A", "B", "C", "D", "E", "F", "G", "H"};
    EXPECT_EQ(keys, expected);
}

TEST_P(TreeTest, DepthPreOrderTraverseTest)
{
    static const DataTree::KeysType EXPECTED(TEST_DATA.cbegin(), TEST_DATA.cend());

    DataTree::KeysType keys;
    _tree->traverse(DataTree::TraverseOrder::DepthPreOrder, [&](const auto& key, auto&) {
        keys.push_back(key);
    });

    EXPECT_EQ(keys, EXPECTED);
}

TEST_P(TreeTest, DepthInOrderTraverseTest)
{
    static const DataTree::KeysType EXPECTED{
        "H", "D", "B", "A", "C", "F", "E",
        "G", "L", "J", "I", "K", "N", "M",
        "O", "P", "T", "R", "Q", "S", "X",
        "V", "U", "W", "Z", "Y"};

    DataTree::KeysType keys;
    _tree->traverse(DataTree::TraverseOrder::DepthInOrder, [&](const auto& key, auto&) {
        keys.push_back(key);
    });

    EXPECT_EQ(keys, EXPECTED);
}

TEST_P(TreeTest, DepthPostOrderTraverseTest)
{
    static const DataTree::KeysType EXPECTED{
        "H", "D", "B", "A", "C", "F", "E",
        "G", "L", "J", "I", "K", "N", "M",
        "O", "T", "R", "Q", "S", "X", "V",
        "U", "W", "Z", "Y", "P"};

    DataTree::KeysType keys;
    _tree->traverse(DataTree::TraverseOrder::DepthPostOrder, [&](const auto& key, auto&) {
        keys.push_back(key);
    });

    EXPECT_EQ(keys, EXPECTED);
}

TEST_P(TreeTest, BreadthOrderTraverseTest)
{
    static const DataTree::KeysType EXPECTED{
        "P", "H", "T", "D", "L", "R", "X",
        "B", "F", "J", "N", "Q", "S", "V",
        "Z", "A", "C", "E", "G", "I", "K",
        "M", "O", "U", "W", "Y"};

    DataTree::KeysType keys;
    _tree->traverse(DataTree::TraverseOrder::Breadth, [&](const auto& key, auto&) {
        keys.push_back(key);
    });

    EXPECT_EQ(keys, EXPECTED);
}

//----------------------------------------------------------------------------------------------------------------------

INSTANTIATE_TEST_SUITE_P(TreeTestMain, TreeTest, ::testing::Values(&getBinarySearchTree, &getRedBlackBinarySearchTree));
