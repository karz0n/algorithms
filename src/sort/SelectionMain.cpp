#include <gtest/gtest.h>

#include "Selection.hpp"

using namespace algorithms;

TEST(Sort, Selection)
{
    std::vector<int> numbers{ 4, 1, 5, 0, 10 };
    Selection::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Selection::isAscending(numbers.begin(), numbers.end()));

    std::vector<char> chars{ 'B', 'A', 'C', 'F', 'L' };
    Selection::sort(chars.begin(), chars.end());
    ASSERT_TRUE(Selection::isAscending(chars.begin(), chars.end()));

    std::vector<std::string> strings{ "About", "New", "Text", "End", "Begin" };
    Selection::sort(strings.begin(), strings.end());
    ASSERT_TRUE(Selection::isAscending(strings.begin(), strings.end()));
}
