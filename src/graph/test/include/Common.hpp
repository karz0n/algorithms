#pragma once

#include "Graph.hpp"
#include "EdgeWeightedGraph.hpp"
#include "EdgeWeightedDigraph.hpp"
#include "FlowNetwork.hpp"

#include <filesystem>

extern void
read(const std::filesystem::path& path, algorithms::Graph& graph);

extern void
read(const std::filesystem::path& path, algorithms::EdgeWeightedGraph& graph);

extern void
read(const std::filesystem::path& path, algorithms::EdgeWeightedDigraph& graph);

extern void
read(const std::filesystem::path& path, algorithms::FlowNetwork& network);
