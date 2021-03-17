#pragma once

#include <string>
#include <string_view>

#include "Digraph.hpp"

namespace algorithms {

/**
 * Regular expression match implementation.
 */
class RegExpMatcher {
public:
    explicit RegExpMatcher(std::string_view pattern);

    [[nodiscard]] bool
    match(std::string_view text) const;

private:
    void
    buildEpsilonTransitions();

private:
    const std::string _pattern;
    Digraph _transitions;
};

} // namespace algorithms