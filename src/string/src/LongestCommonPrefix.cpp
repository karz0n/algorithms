#include "LongestCommonPrefix.hpp"

#include "ThreeWayRadixSort.hpp"

#include <vector>

namespace algorithms {

std::string
LongestCommonPrefix::find(const std::string_view& input)
{
    using SuffixArray = std::vector<std::string_view>;

    SuffixArray array;
    for (std::size_t n = 0; n < input.length(); ++n) {
        array.push_back(input.substr(n));
    }

    ThreeWayRadixSort::sort(array);

    std::string_view longestPrefix;
    for (std::size_t i = 0; i < input.length() - 1; ++i) {
        const auto prefix = getCommonPrefixLength(array[i], array[i + 1]);
        if (prefix.length() > longestPrefix.length()) {
            longestPrefix = prefix;
        }
    }

    return std::string(longestPrefix);
}

std::string_view
LongestCommonPrefix::getCommonPrefixLength(const std::string_view& lh, const std::string_view& rh)
{
    std::size_t length{0};
    for (std::size_t i = 0; i < lh.length() && i < rh.length(); ++i, ++length) {
        if (lh[i] != rh[i]) {
            break;
        }
    }
    return lh.substr(0, length);
}

} // namespace algorithms