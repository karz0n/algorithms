#pragma once

#include <Graph.hpp>

#include <filesystem>

namespace fs = std::filesystem;

extern void
readGraph(const fs::path& path, algorithms::Graph& graph);
