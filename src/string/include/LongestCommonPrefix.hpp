#pragma once

#include <string>

namespace algorithms {

class LongestCommonPrefix {
public:
    static std::string find(const std::string_view& input);

private:
    static std::string_view
    getCommonPrefixLength(const std::string_view& lh, const std::string_view& rh);
};

}