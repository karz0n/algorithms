#ifndef COMMON_HPP
#define COMMON_HPP

#include <chrono>
#include <vector>
#include <utility>
#include <functional>
#include <filesystem>

namespace fs = std::filesystem;

namespace algorithms
{
namespace uf
{

/** Path to */
extern fs::path TINY_UNIONS_PATH;

/** Path to */
extern fs::path MEDIUM_UNIONS_PATH;

/** Path to */
extern fs::path LARGE_UNIONS_PATH;

/**
 *
 */
using Union = std::pair<std::size_t, std::size_t>;

/**
 *
 */
using Unions = std::vector<Union>;

/**
 * Reads unions from file.
 *
 * @param path The path to the particular file.
 *
 * @return An array of readed unions.
 */
Unions readUnionsFromFile(const fs::path& path);

/**
 *
 * @param callable
 */
std::chrono::nanoseconds measure(std::function<void()> callable);

/**
 *
 * @param path
 */
void printMeasure(const fs::path& path, std::size_t count, const std::chrono::nanoseconds& time);

/**
 *
 * @param us
 *
 * @return
 */
std::string formatTime(std::chrono::nanoseconds time);

} // namespace uf
} // namespace algorithms

#endif // COMMON_HPP
