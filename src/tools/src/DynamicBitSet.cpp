#include "DynamicBitSet.hpp"

#include <stdexcept>

namespace algorithms {

DynamicBitSet::DynamicBitSet(std::initializer_list<bool> bits)
{
    putBits(bits);
}

DynamicBitSet::DynamicBitSet(std::initializer_list<std::byte> bytes)
{
    putBytes(bytes);
}

DynamicBitSet::Base::reference
DynamicBitSet::operator[](std::size_t pos)
{
    return _base[pos];
}

DynamicBitSet::Base::const_reference
DynamicBitSet::operator[](std::size_t pos) const
{
    return _base[pos];
}

bool
DynamicBitSet::operator==(const DynamicBitSet& other) const
{
    if (this != &other) {
        return (_base == other._base);
    }
    return true;
}

bool
DynamicBitSet::operator!=(const DynamicBitSet& other) const
{
    return !(*this == other);
}

DynamicBitSet&
DynamicBitSet::operator+=(const DynamicBitSet& other)
{
    if (this != &other) {
        _base.insert(_base.cend(), other._base.cbegin(), other._base.cend());
    }
    return *this;
}

void
DynamicBitSet::putBit(bool value)
{
    _base.push_back(value);
}

void
DynamicBitSet::putBits(std::initializer_list<bool> bits)
{
    for (const bool bit : bits) {
        putBit(bit);
    }
}

void
DynamicBitSet::putBits(std::uint64_t value, std::size_t count)
{
    static const std::size_t MaxCount = sizeof(value) * BitsInByte;
    if (count >= MaxCount) {
        throw std::runtime_error{"Invalid count value"};
    }

    std::size_t nth{0};
    while (nth < count) {
        const std::uint64_t mask = (1UL << nth);
        putBit((value & mask) != 0);
        nth++;
    }
}

void
DynamicBitSet::putByte(std::byte value)
{
    std::size_t nth{0};
    while (nth < BitsInByte) {
        const std::byte mask = std::byte{0b1} << nth;
        putBit((value & mask) != std::byte{0b0});
        nth++;
    }
}

void
DynamicBitSet::putBytes(std::initializer_list<std::byte> bytes)
{
    for (const std::byte byte : bytes) {
        putByte(byte);
    }
}

bool
DynamicBitSet::popBit()
{
    const bool bit = _base.back();
    _base.pop_back();
    return bit;
}

std::byte
DynamicBitSet::popByte(std::endian order)
{
    std::byte value{0};
    std::size_t nth{0};
    while (nth < BitsInByte) {
        if (popBit()) {
            const std::size_t shift{(order == std::endian::big) ? BitsInByte - nth - 1 : nth};
            value |= std::byte{0b1} << shift;
        }
        nth++;
    }
    return value;
}

std::uint64_t
DynamicBitSet::popBits(std::size_t count, std::endian order)
{
    std::uint64_t value{0};

    static const unsigned MaxCount = sizeof(value) * BitsInByte;
    if (count >= MaxCount) {
        throw std::runtime_error{"Invalid count value"};
    }

    std::size_t nth{0};
    while (nth < count) {
        if (popBit()) {
            const auto shift{(order == std::endian::big) ? count - nth - 1 : nth};
            value |= 1UL << shift;
        }
        nth++;
    }

    return value;
}

std::size_t
DynamicBitSet::size() const
{
    return _base.size();
}

bool
DynamicBitSet::empty() const
{
    return _base.empty();
}

[[nodiscard]] DynamicBitSet
DynamicBitSet::reverse() const
{
    return DynamicBitSet{_base.crbegin(), _base.crend()};
}

} // namespace algorithms