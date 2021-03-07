#pragma once

#include <string_view>

namespace algorithms {

/**
 * The Rabin-Karp substring search algorithm implementation.
 */
template<typename Ch = char>
class RabinKarpSubstringSearch {
public:
    static constexpr int NotFound = -1;

    /** The number of possible character values */
    static constexpr std::size_t R = std::numeric_limits<Ch>::max() + 1;
    /** The random big prime number */
    static constexpr std::size_t Q = 841'642'723;

    static int search(std::basic_string_view<Ch> text, std::basic_string_view<Ch> pattern)
    {
        std::size_t N{text.size()};
        std::size_t M{pattern.size()};

        const auto patternHash = hash(pattern);

        // Precompute R^(M-1) value
        std::size_t Rm{1};
        for (std::size_t i = 1; i <= M - 1; ++i) {
            Rm = (R * Rm) % Q;
        }

        // Compute hash of first M characters
        auto textHash = hash(text.substr(0, M));
        if (patternHash == textHash) {
            return 0;
        }

        // Compute hash of next bunch of characters
        for (std::size_t i{M}; i < N; ++i) {
            textHash = (textHash + Q - Rm * text[i - M] % Q) % Q;
            textHash = (textHash * R + text[i]) % Q;
            if (patternHash == textHash) {
                return i - M + 1u;
            }
        }

        return NotFound;
    }

private:
    static std::size_t hash(std::basic_string_view<Ch> key)
    {
        std::size_t output{0};
        for (Ch ch : key) {
            output = (output * R + ch) % Q;
        }
        return output;
    }
};

}