#pragma once

#include "traverse/DepthPreOrderTraverse.hpp"
#include "traverse/DepthPreOrderNoRecTraverse.hpp"
#include "traverse/DepthInOrderTraverse.hpp"
#include "traverse/DepthInOrderNoRecTraverse.hpp"
#include "traverse/DepthPostOrderTraverse.hpp"
#include "traverse/DepthPostOrderNoRecTraverse.hpp"
#include "traverse/BreadthOrderTraverse.hpp"

namespace algorithms {

enum class TraverseOrder { DepthPreOrder, DepthInOrder, DepthPostOrder, BreadthOrder };

} // namespace algorithms
