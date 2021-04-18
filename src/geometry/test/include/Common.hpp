#pragma once

#include "Points.hpp"

#include <filesystem>

extern void
read(const std::filesystem::path& path, algorithms::Points& points);