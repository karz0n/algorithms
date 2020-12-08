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

extern algorithms::EdgeWeightedDigraph
readEdgeWeightedDigraph(const std::filesystem::path& path);

extern void
verifyMinSpanningTree(const algorithms::Edges& tree, const algorithms::EdgeWeightedGraph& graph);