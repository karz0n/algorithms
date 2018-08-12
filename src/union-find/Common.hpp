#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>
#include <utility>
#include <functional>

namespace algorithms
{
namespace uf
{

using Union = std::pair<std::size_t, std::size_t>;
using Unions = std::vector<Union>;

/**
 * Reads unions from file
 * @param path the path to the particular file
 * @return an array of readed unions
 */
Unions readUnionsFromFile(const std::string& path);

/**
 * @brief run
 * @param callable
 */
void run(std::function<void()> callable);

} // namespace uf
} // namespace algorithms

#endif // COMMON_HPP
