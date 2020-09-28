#pragma once

#include "Graph.hpp"
#include "EdgeWeightedGraph.hpp"

#include <filesystem>

namespace fs = std::filesystem;

extern void
readGraph(const fs::path& path, algorithms::Graph& graph);

extern void
readGraph(const fs::path& path, algorithms::EdgeWeightedGraph& graph);