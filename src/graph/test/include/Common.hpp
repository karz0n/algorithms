#pragma once

#include <Graph.hpp>

#include <filesystem>

namespace fs = std::filesystem;

void
read(const fs::path& path, algorithms::Graph& graph);
