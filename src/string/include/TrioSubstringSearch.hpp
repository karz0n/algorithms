#pragma once

#include <array>
#include <string_view>
#include <vector>
#include <limits>

namespace algorithms {

/**
 * The Knuth-Morris-Pratt substring search algorithm implementation.
 */
template<typename Ch = char>
class TrioSubstringSearch {
public:
    static constexpr int NotFound = -1;

    static std::size_t
    search(std::basic_string_view<Ch> text, std::basic_string_view<Ch> pattern)
    {
        Automaton automaton{pattern};

        std::size_t n{0};
        for (; n < text.size() && automaton.hasNext(); ++n) {
            automaton.next(text[n]);
        }

        return automaton.hasNext() ? NotFound : n - pattern.size();
    }

private:
    /** The number of possible character values */
    static constexpr std::size_t R = std::numeric_limits<Ch>::max() + 1;

    class Automaton {
        using States = std::array<std::vector<std::size_t>, R>;

    public:
        explicit Automaton(std::basic_string_view<Ch> pattern)
            : _currState{0}
            , _tailState{pattern.size()}
        {
            construct(pattern);
        }

        [[maybe_unused]] bool
        next(Ch ch)
        {
            _currState = _states[ch][_currState];
            return hasNext();
        }

        [[nodiscard]] bool
        hasNext() const
        {
            return (_currState != _tailState);
        }

    private:
        void
        construct(std::string_view pattern)
        {
            // Init states
            for (std::size_t r = 0; r < R; ++r) {
                _states[r].resize(_tailState, 0);
            }

            _states[pattern.at(0)][0] = 1;
            for (std::size_t x = 0, j = 1; j < _tailState; ++j) {
                // Set mismatch states
                for (std::size_t r = 0; r < R; ++r) {
                    _states[r][j] = _states[r][x];
                }

                // Set match state
                _states[pattern.at(j)][j] = j + 1;

                // Update mismatch position where we could be with first item left
                x = _states[pattern.at(j)][x];
            }
        }

    private:
        States _states;
        std::size_t _currState;
        std::size_t _tailState;
    };
};

} // namespace algorithms