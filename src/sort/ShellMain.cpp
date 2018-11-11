#include <gtest/gtest.h>

#include "Shell.hpp"

using namespace algorithms;

TEST(Sort, Shell)
{
    std::vector<int> numbers{ 4, 1, 5, 0, 10 };
    Shell::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Shell::isAscending(numbers.begin(), numbers.end()));

    std::vector<char> chars{ 'B', 'A', 'C', 'F', 'L' };
    Shell::sort(chars.begin(), chars.end());
    ASSERT_TRUE(Shell::isAscending(chars.begin(), chars.end()));

    std::vector<std::string> strings{ "About", "New", "Text", "End", "Begin" };
    Shell::sort(strings.begin(), strings.end());
    ASSERT_TRUE(Shell::isAscending(strings.begin(), strings.end()));
}
