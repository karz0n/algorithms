#include "TreeTestData.hpp"

using namespace algorithms;

static void
fillByTestData(TestFileDataTreePtr to)
{
    std::for_each(TEST_DATA.cbegin(), TEST_DATA.cend(), [&](const auto& d) { to->put(d, d); });
}

TestFileDataTreePtr
getBinarySearchTree()
{
    auto tree = std::make_shared<BinarySearchDataTree>();
    fillByTestData(tree);
    return std::move(tree);
}

TestFileDataTreePtr
getRedBlackBinarySearchTree()
{
    auto tree = std::make_shared<RedBlackBinarySearchDataTree>();
    fillByTestData(tree);
    return std::move(tree);
}
