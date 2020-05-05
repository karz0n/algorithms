#pragma once

#include <Graph.hpp>

#include <filesystem>

namespace fs = std::filesystem;

algorithms::Graph
read(const fs::path& path);
