#pragma once

#include <array>
#include <memory>

#include <BinarySearchTree.hpp>
#include <RedBlackBinarySearchTree.hpp>

const std::size_t TEST_DATA_SIZE = 26;
const std::array<std::string, TEST_DATA_SIZE> TEST_DATA{
    "P", "H", "D", "B", "A", "C", "F",
    "E", "G", "L", "J", "I", "K", "N",
    "M", "O", "T", "R", "Q", "S", "X",
    "V", "U", "W", "Z", "Y"};

using DataTree = algorithms::Tree<std::string, std::string>;
using TestFileDataTreePtr = std::shared_ptr<DataTree>;

using BinarySearchDataTree = algorithms::BinarySearchTree<DataTree::KeyType, DataTree::ValueType>;
using BinarySearchDataTreePtr = std::shared_ptr<BinarySearchDataTree>;

using RedBlackBinarySearchDataTree = algorithms::RedBlackBinarySearchTree<DataTree::KeyType, DataTree::ValueType>;
using RedBlackBinarySearchDataTreePtr = std::shared_ptr<RedBlackBinarySearchDataTree>;

extern TestFileDataTreePtr
getBinarySearchTree();

extern TestFileDataTreePtr
getRedBlackBinarySearchTree();
