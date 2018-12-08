#ifndef COMMON_HPP
#define COMMON_HPP

#include <chrono>
#include <functional>

namespace algorithms {

/**
 *
 * @param callable
 */
std::chrono::nanoseconds measure(std::function<void()> callable);

/**
 *
 */
void printMeasure(const std::string& title, const std::chrono::nanoseconds& time);

/**
 *
 * @param us
 *
 * @return
 */
std::string formatTime(std::chrono::nanoseconds time);

} // namespace algorithms

#endif // COMMON_HPP
