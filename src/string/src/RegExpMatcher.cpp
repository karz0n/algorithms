#include "RegExpMatcher.hpp"

#include "DepthFirstRoutes.hpp"

#include <stack>
#include <algorithm>

namespace algorithms {

RegExpMatcher::RegExpMatcher(std::string_view pattern)
    : _pattern{pattern}
    , _transitions{_pattern.size() + 1}
{
    buildEpsilonTransitions();
}

bool
RegExpMatcher::match(std::string_view text) const
{
    const auto TerminalState = _transitions.verticesCount() - 1;

    DepthFirstRoutes routes{_transitions, 0};
    auto states{routes.reachability()};
    for (const auto ch : text) {
        decltype(states) match;
        for (auto state : states) {
            if (state == TerminalState) {
                return true;
            }
            if (_pattern[state] == ch || _pattern[state] == '.') {
                match.push_back(state + 1);
            }
        }
        routes = DepthFirstRoutes{_transitions, match};
        states = routes.reachability();
    }

    return std::ranges::any_of(states, [&](auto s) { return (s == TerminalState); });
}

void
RegExpMatcher::buildEpsilonTransitions()
{
    const auto PatternLength = _pattern.size();

    std::stack<std::size_t> ops;
    for (std::size_t i{0}, lp{0}; i < PatternLength; ++i, lp = i) {
        const auto ch = _pattern[i];
        if (ch == '(' || ch == '|') {
            ops.push(i);
        }
        else if (ch == ')') {
            const auto op = ops.top();
            ops.pop();
            if (_pattern[op] == '|') {
                lp = ops.top();
                ops.pop();
                _transitions.connect(lp, op + 1);
                _transitions.connect(op, i);
            }
            else {
                lp = op;
            }
        }

        if (i < PatternLength - 1 && _pattern[i + 1] == '*') {
            _transitions.connect(lp, i + 1);
            _transitions.connect(i + 1, lp);
        }

        if (ch == '(' || ch == '*' || ch == ')') {
            _transitions.connect(i, i + 1);
        }
    }
}

} // namespace algorithms