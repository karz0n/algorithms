#pragma once

#include <string>
#include <vector>
#include <string_view>

namespace algorithms::lzw {

constexpr std::size_t R = 256;
constexpr std::size_t L = 4096;
constexpr std::size_t W = 12;

using Byte = std::uint8_t;
using Bytes = std::vector<Byte>;

[[nodiscard]] Bytes
encode(std::string_view input);

[[nodiscard]] std::string
decode(Bytes bytes);

} // namespace algorithms::lzw