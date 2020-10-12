#include <gtest/gtest.h>

#include <IntervalSearchTree.hpp>

using namespace algorithms;

TEST(IntervalSearchTreeTest, Get)
{
    IntervalSearchTree<int, std::string> tree;
    EXPECT_TRUE(tree.empty());
    tree.put(1, 5, "R1");
    EXPECT_EQ(tree.get(1, 5), "R1");
}

TEST(IntervalSearchTreeTest, Erase)
{
    IntervalSearchTree<int, std::string> tree;
    tree.put(1, 5, "R1");
    EXPECT_FALSE(tree.empty());
    tree.erase(1, 5);
    EXPECT_THROW([[maybe_unused]] auto v = tree.get(1, 5), std::exception);
    EXPECT_TRUE(tree.empty());
}

TEST(IntervalSearchTreeTest, Intersects)
{
    IntervalSearchTree<int, std::string> tree;
    tree.put(1, 3, "R1");
    tree.put(2, 8, "R2");
    auto r = tree.intersects(3, 5);
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), "R1");
}
