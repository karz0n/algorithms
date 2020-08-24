#include <gtest/gtest.h>

#include <LinearProbingHashTree.hpp>

#include <string>

using namespace algorithms;

TEST(LinearProbingHashTreeTest, PutAndGet)
{
    LinearProbingHashTree<std::string, int> tree;

    tree.put("A", 0);
    tree.put("B", 1);
    tree.put("C", 2);

    EXPECT_EQ(tree.get("A"), 0);
    EXPECT_EQ(tree.get("B"), 1);
    EXPECT_EQ(tree.get("C"), 2);
}
