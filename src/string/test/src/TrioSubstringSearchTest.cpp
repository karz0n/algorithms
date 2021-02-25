#include <gtest/gtest.h>

#include "TrioSubstringSearch.hpp"

using namespace algorithms;
using namespace testing;

using CharTrioSubstringSearch = TrioSubstringSearch<char>;

TEST(TrioSubstringSearchTest, Find)
{
    static const std::string_view text{"Peter Piper picked a peck of pickled peppers\n"
                                       "A peck of pickled peppers Peter Piper picked\n"
                                       "If Peter Piper picked a peck of pickled peppers\n"
                                       "Where’s the peck of pickled peppers Peter Piper picked?"};

    static const std::string_view pattern{"pepper"};

    const auto p1 = CharTrioSubstringSearch::search(text, pattern);
    const auto p2 = text.find(pattern);
    EXPECT_EQ(p1, p2);
}