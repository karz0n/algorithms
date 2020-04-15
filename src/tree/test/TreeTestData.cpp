#include "TreeTestData.hpp"

using namespace algorithms;

static void
fillByTestData(TestFileDataTreePtr to)
{
    std::for_each(TEST_DATA.cbegin(), TEST_DATA.cend(), [&](const auto& d) { to->put(d, d); });
}

TestFileDataTreePtr
getBinaryTree()
{
    auto tree = std::make_shared<BinaryDataTree>();
    fillByTestData(tree);
    return std::move(tree);
}

TestFileDataTreePtr
getRedBlackTree()
{
    auto tree = std::make_shared<RedBlackDataTree>();
    fillByTestData(tree);
    return std::move(tree);
}
