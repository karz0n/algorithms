#pragma once

#include <array>
#include <memory>

#include <BinaryTree.hpp>
#include <RedBlackTree.hpp>

const std::size_t TEST_DATA_SIZE = 26;
const std::array<std::string, TEST_DATA_SIZE> TEST_DATA{
    "P", "H", "D", "B", "A", "C", "F",
    "E", "G", "L", "J", "I", "K", "N",
    "M", "O", "T", "R", "Q", "S", "X",
    "V", "U", "W", "Z", "Y"};

using DataTree = algorithms::Tree<std::string, std::string>;
using TestFileDataTreePtr = std::shared_ptr<DataTree>;

using BinaryDataTree = algorithms::BinaryTree<DataTree::KeyType, DataTree::ValueType>;
using BinaryDataTreePtr = std::shared_ptr<BinaryDataTree>;

using RedBlackDataTree = algorithms::RedBlackTree<DataTree::KeyType, DataTree::ValueType>;
using RedBlackDataTreePtr = std::shared_ptr<RedBlackDataTree>;

extern TestFileDataTreePtr
getBinaryTree();

extern TestFileDataTreePtr
getRedBlackTree();
