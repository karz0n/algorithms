#include "SHA1.hpp"

#include <bit>
#include <stdexcept>

namespace {

std::uint32_t
doF1(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return (x & y) | (~x & z);
}

std::uint32_t
doF2(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return (x ^ y ^ z);
}

std::uint32_t
doF3(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return (x & y) | (x & z) | (y & z);
}

std::uint32_t
doF4(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return (x ^ y ^ z);
}

} // namespace

namespace algorithms {

SHA1::SHA1()
    : _index{}
    , _state{}
    , _count{}
    , _buffer{}
    , _digest{}
{
    reset();
}

void
SHA1::update(const void* data, std::size_t size)
{
    if (!data || size == 0) {
        throw std::invalid_argument{"Invalid pointer value"};
    }

    // Update index
    _index = size & 0x3F;

    // Update number of bits
    const std::uint64_t bitCount{size << 3};
    _count[0] += bitCount;
    _count[1] += size >> 29;
    if (bitCount > _count[0]) {
        _count[1]++;
    }

    // Transform as many times as possible
    const auto* castData = static_cast<const std::uint8_t*>(data);
    std::size_t count, offset{0};
    while (size) {
        count = std::min<std::size_t>(size, BufferBytesCount);
        std::copy_n(castData + offset, count, _buffer.begin());
        if (count == BufferBytesCount) {
            transform(_buffer, _state);
            offset += BufferBytesCount;
        }
        size -= count;
    }
}

void
SHA1::reset()
{
    _index = 0;

    _count[0] = 0;
    _count[1] = 0;

    _state[0] = 0x67452301;
    _state[1] = 0xEFCDAB89;
    _state[2] = 0x98BADCFE;
    _state[3] = 0x10325476;
    _state[4] = 0xC3D2E1F0;

    _buffer.fill(0);
    _digest.fill(0);
}

Digest
SHA1::finalize()
{
    // Pad out to 56 mod 64
    _buffer[_index++] = 0x80;
    if (_index > 56) {
        std::fill_n(_buffer.begin() + _index, 64 - _index, 0);
        transform(_buffer, _state);
        _index = 0;
    }
    std::fill_n(_buffer.begin() + _index, 56 - _index, 0);

    // Append length
    _buffer[56] = (_count[1] >> 24) & 0xFF;
    _buffer[57] = (_count[1] >> 16) & 0xFF;
    _buffer[58] = (_count[1] >> 8) & 0xFF;
    _buffer[59] = _count[1] & 0xFF;
    _buffer[60] = (_count[0] >> 24) & 0xFF;
    _buffer[61] = (_count[0] >> 16) & 0xFF;
    _buffer[62] = (_count[0] >> 8) & 0xFF;
    _buffer[63] = _count[0] & 0xFF;

    // Transform
    transform(_buffer, _state);
    for (std::size_t i{0}; i < DigestBytesCount; ++i) {
        _digest[i] = static_cast<std::uint8_t>(_state[i >> 2] >> 8 * (3 - (i & 0x03)));
    }

    // Set to zero sensitive information
    _index = 0;
    _count[0] = 0;
    _count[1] = 0;
    _state.fill(0);
    _buffer.fill(0);

    return Digest{_digest.data(), DigestBytesCount};
}

std::size_t
SHA1::length() const
{
    return DigestBytesCount;
}

void
SHA1::transform(const BufferArray& buffer, StateArray& state)
{
    static const std::uint32_t K[] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};

    // Initialize the first 16 words in the array w
    std::array<std::uint32_t, 80> w{};
    for (std::size_t i{0}; i < 16; ++i) {
        w[i] = buffer[i * 4] << 24;
        w[i] |= buffer[i * 4 + 1] << 16;
        w[i] |= buffer[i * 4 + 2] << 8;
        w[i] |= buffer[i * 4 + 3];
    }
    for (std::size_t i{16}; i < 80; ++i) {
        w[i] = std::rotl(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    }

    std::uint32_t a = state[0];
    std::uint32_t b = state[1];
    std::uint32_t c = state[2];
    std::uint32_t d = state[3];
    std::uint32_t e = state[4];

    // 1
    for (std::size_t i{0}; i < 20; ++i) {
        std::uint32_t temp = std::rotl(a, 5) + doF1(b, c, d) + e + w[i] + K[0];
        e = d;
        d = c;
        c = std::rotl(b, 30);
        b = a;
        a = temp;
    }

    // 2
    for (std::size_t i{20}; i < 40; ++i) {
        std::uint32_t temp = std::rotl(a, 5) + doF2(b, c, d) + e + w[i] + K[1];
        e = d;
        d = c;
        c = std::rotl(b, 30);
        b = a;
        a = temp;
    }

    // 3
    for (std::size_t i{40}; i < 60; ++i) {
        std::uint32_t temp = std::rotl(a, 5) + doF3(b, c, d) + e + w[i] + K[2];
        e = d;
        d = c;
        c = std::rotl(b, 30);
        b = a;
        a = temp;
    }

    // 4
    for (std::size_t i{60}; i < 80; ++i) {
        std::uint32_t temp = std::rotl(a, 5) + doF4(b, c, d) + e + w[i] + K[3];
        e = d;
        d = c;
        c = std::rotl(b, 30);
        b = a;
        a = temp;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}

} // namespace algorithms