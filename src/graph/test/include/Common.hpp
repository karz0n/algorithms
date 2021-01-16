#pragma once

#include "Graph.hpp"
#include "EdgeWeightedGraph.hpp"
#include "EdgeWeightedDigraph.hpp"

#include <filesystem>

extern void
readGraph(const std::filesystem::path& path, algorithms::Graph& graph);

extern void
readGraph(const std::filesystem::path& path, algorithms::EdgeWeightedGraph& graph);

extern void
readGraph(const std::filesystem::path& path, algorithms::EdgeWeightedDigraph& graph);
