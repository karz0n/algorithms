#pragma once

#include <bit>
#include <concepts>
#include <stdexcept>

namespace algorithms {

class ByteOrder {
public:
    template<std::unsigned_integral T>
    static constexpr T
    convert(T value, std::endian from, std::endian to)
    {
        static_assert(sizeof(T) >= 2 && sizeof(T) <= 8, "Invalid size of input value");
#ifndef NDEBUG
        if ((from != std::endian::big && from != std::endian::little) || (to != std::endian::big && to != std::endian::little)) {
            throw std::runtime_error{"Middle-endian not supported"};
        }
#endif
        return (from == to) ? value : reverseBytes(value);
    }

private:
    static constexpr std::uint16_t
    reverseBytes(std::uint16_t value)
    {
        return (((value >> 8) & 0xFF) | ((value << 8) & 0xFF00));
    }

    static constexpr std::uint32_t
    reverseBytes(std::uint32_t value)
    {
        const auto hi = static_cast<std::uint16_t>(value >> 16);
        const auto lo = static_cast<std::uint16_t>(value & 0xFFFF);
        return (static_cast<std::uint32_t>(reverseBytes(hi)) | (static_cast<std::uint32_t>(reverseBytes(lo)) << 16));
    }

    static constexpr std::uint64_t
    reverseBytes(std::uint64_t value)
    {
        const auto hi = static_cast<std::uint32_t>(value >> 32);
        const auto lo = static_cast<std::uint32_t>(value & 0xFFFFFFFF);
        return (static_cast<std::uint64_t>(reverseBytes(hi)) | (static_cast<std::uint64_t>(reverseBytes(lo)) << 32));
    }
};

} // namespace algorithms
