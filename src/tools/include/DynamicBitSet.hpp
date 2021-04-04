#pragma once

#include <bit>
#include <vector>

#include <cstdint>
#include <cstddef>

namespace algorithms {

class DynamicBitSet {
public:
    static constexpr std::size_t BitsInByte = 8;

    using Base = std::vector<bool>;

    DynamicBitSet() = default;

    DynamicBitSet(std::initializer_list<bool> bits);

    DynamicBitSet(std::initializer_list<std::byte> bytes);

    Base::reference
    operator[](std::size_t pos);

    Base::const_reference
    operator[](std::size_t pos) const;

    bool
    operator==(const DynamicBitSet& other) const;

    bool
    operator!=(const DynamicBitSet& other) const;

    DynamicBitSet&
    operator+=(const DynamicBitSet& other);

    void
    putBit(bool bit);

    void
    putBits(std::initializer_list<bool> bits);

    void
    putBits(std::uint64_t value, std::size_t count);

    void
    putByte(std::byte value);

    void
    putBytes(std::initializer_list<std::byte> bytes);

    bool
    popBit();

    [[nodiscard]] std::uint64_t
    popBits(std::size_t count, std::endian order = std::endian::big);

    [[nodiscard]] std::byte
    popByte(std::endian order = std::endian::big);

    [[nodiscard]] std::size_t
    size() const;

    [[nodiscard]] bool
    empty() const;

    [[nodiscard]] DynamicBitSet
    reverse() const;

private:
    template<typename It>
    DynamicBitSet(It first, It last)
        : _base{first, last}
    {
    }

private:
    Base _base;
};

} // namespace algorithms