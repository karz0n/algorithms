#include "MD5.hpp"

#include <bit>
#include <stdexcept>

namespace {

std::uint32_t
doF(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return (x & y) | (~x & z);
}

std::uint32_t
doG(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return (x & z) | (y & ~z);
}

std::uint32_t
doH(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return x ^ y ^ z;
}

std::uint32_t
doI(std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
    return y ^ (x | ~z);
}

std::uint32_t
doFF(std::uint32_t a,
     std::uint32_t b,
     std::uint32_t c,
     std::uint32_t d,
     std::uint32_t x,
     std::uint32_t s,
     std::uint32_t ac)
{
    a += doF(b, c, d) + x + ac;
    a = std::rotl(a, static_cast<int>(s)) + b;
    return a;
}

std::uint32_t
doGG(std::uint32_t a,
     std::uint32_t b,
     std::uint32_t c,
     std::uint32_t d,
     std::uint32_t x,
     std::uint32_t s,
     std::uint32_t ac)
{
    a += doG(b, c, d) + x + ac;
    a = std::rotl(a, static_cast<int>(s)) + b;
    return a;
}

std::uint32_t
doHH(std::uint32_t a,
     std::uint32_t b,
     std::uint32_t c,
     std::uint32_t d,
     std::uint32_t x,
     std::uint32_t s,
     std::uint32_t ac)
{
    a += doH(b, c, d) + x + ac;
    a = std::rotl(a, static_cast<int>(s)) + b;
    return a;
}

std::uint32_t
doII(std::uint32_t a,
     std::uint32_t b,
     std::uint32_t c,
     std::uint32_t d,
     std::uint32_t x,
     std::uint32_t s,
     std::uint32_t ac)
{
    a += doI(b, c, d) + x + ac;
    a = std::rotl(a, static_cast<int>(s)) + b;
    return a;
}

} // namespace

namespace algorithms {

MD5::MD5()
    : _count{}
    , _state{}
    , _buffer{}
    , _digest{}
{
    reset();
}

void
MD5::update(const void* data, std::size_t size)
{
    if (!data || size == 0) {
        std::invalid_argument error("Invalid arguments");
        return;
    }

    // Compute number of bytes mod 64
    std::size_t index{(_count[0] >> 3) & 0x3F};

    // Update number of bits
    const std::size_t bitCount = size << 3;
    _count[0] += bitCount;
    _count[1] += size >> 29;
    if (bitCount > _count[0]) {
        _count[1]++;
    }

    // Transform chunks as many times as possible
    const auto* castData = static_cast<const std::uint8_t*>(data);
    std::size_t offset, partLen{BufferBytesCount - index};
    if (size < partLen) {
        offset = 0;
    } else {
        std::copy_n(castData, partLen, _buffer.begin() + index);
        transform(_buffer, _state);
        for (offset = partLen; offset + (BufferBytesCount - 1) < size; offset += BufferBytesCount) {
            std::copy_n(castData, BufferBytesCount, _buffer.begin());
            transform(_buffer, _state);
        }
        index = 0;
    }

    // Buffer remaining input
    std::copy_n(castData + offset, size - offset, _buffer.begin() + index);
}

void
MD5::reset()
{
    _count[0] = 0;
    _count[1] = 0;

    _state[0] = 0x67452301;
    _state[1] = 0xefcdab89;
    _state[2] = 0x98badcfe;
    _state[3] = 0x10325476;

    _buffer.fill(0);
    _digest.fill(0);
}

Digest
MD5::finalize()
{
    static const std::uint8_t placeholder[BufferBytesCount] = {0x80};

    // Save number of bits
    std::array<std::uint8_t, 8> bits{};
    encode(_count, bits);

    // Pad out to 56 mod 64
    const std::size_t index = (_count[0] >> 3) & 0x3F;
    const std::size_t size = (index < 56) ? (56 - index) : (120 - index);
    update(placeholder, size);

    // Append length
    update(bits.data(), sizeof bits);

    // Store state in digest
    encode(_state, _digest);

    // Zero buffer
    _buffer.fill(0);

    // Zero sensitive information
    _count.fill(0);
    _state.fill(0);

    return Digest(_digest.data(), DigestBytesCount);
}

std::size_t
MD5::length() const
{
    return DigestBytesCount;
}

void
MD5::transform(const BufferArray& buffer, StateArray& state)
{
    static const std::uint32_t S11 = 7;
    static const std::uint32_t S12 = 12;
    static const std::uint32_t S13 = 17;
    static const std::uint32_t S14 = 22;
    static const std::uint32_t S21 = 5;
    static const std::uint32_t S22 = 9;
    static const std::uint32_t S23 = 14;
    static const std::uint32_t S24 = 20;
    static const std::uint32_t S31 = 4;
    static const std::uint32_t S32 = 11;
    static const std::uint32_t S33 = 16;
    static const std::uint32_t S34 = 23;
    static const std::uint32_t S41 = 6;
    static const std::uint32_t S42 = 10;
    static const std::uint32_t S43 = 15;
    static const std::uint32_t S44 = 21;

    std::uint32_t a = state[0];
    std::uint32_t b = state[1];
    std::uint32_t c = state[2];
    std::uint32_t d = state[3];

    std::array<std::uint32_t, 16> chunk{};
    decode(buffer, chunk);

    // Round 1
    a = doFF(a, b, c, d, chunk[0], S11, 0xd76aa478);
    d = doFF(d, a, b, c, chunk[1], S12, 0xe8c7b756);
    c = doFF(c, d, a, b, chunk[2], S13, 0x242070db);
    b = doFF(b, c, d, a, chunk[3], S14, 0xc1bdceee);
    a = doFF(a, b, c, d, chunk[4], S11, 0xf57c0faf);
    d = doFF(d, a, b, c, chunk[5], S12, 0x4787c62a);
    c = doFF(c, d, a, b, chunk[6], S13, 0xa8304613);
    b = doFF(b, c, d, a, chunk[7], S14, 0xfd469501);
    a = doFF(a, b, c, d, chunk[8], S11, 0x698098d8);
    d = doFF(d, a, b, c, chunk[9], S12, 0x8b44f7af);
    c = doFF(c, d, a, b, chunk[10], S13, 0xffff5bb1);
    b = doFF(b, c, d, a, chunk[11], S14, 0x895cd7be);
    a = doFF(a, b, c, d, chunk[12], S11, 0x6b901122);
    d = doFF(d, a, b, c, chunk[13], S12, 0xfd987193);
    c = doFF(c, d, a, b, chunk[14], S13, 0xa679438e);
    b = doFF(b, c, d, a, chunk[15], S14, 0x49b40821);

    // Round 2
    a = doGG(a, b, c, d, chunk[1], S21, 0xf61e2562);
    d = doGG(d, a, b, c, chunk[6], S22, 0xc040b340);
    c = doGG(c, d, a, b, chunk[11], S23, 0x265e5a51);
    b = doGG(b, c, d, a, chunk[0], S24, 0xe9b6c7aa);
    a = doGG(a, b, c, d, chunk[5], S21, 0xd62f105d);
    d = doGG(d, a, b, c, chunk[10], S22, 0x02441453);
    c = doGG(c, d, a, b, chunk[15], S23, 0xd8a1e681);
    b = doGG(b, c, d, a, chunk[4], S24, 0xe7d3fbc8);
    a = doGG(a, b, c, d, chunk[9], S21, 0x21e1cde6);
    d = doGG(d, a, b, c, chunk[14], S22, 0xc33707d6);
    c = doGG(c, d, a, b, chunk[3], S23, 0xf4d50d87);
    b = doGG(b, c, d, a, chunk[8], S24, 0x455a14ed);
    a = doGG(a, b, c, d, chunk[13], S21, 0xa9e3e905);
    d = doGG(d, a, b, c, chunk[2], S22, 0xfcefa3f8);
    c = doGG(c, d, a, b, chunk[7], S23, 0x676f02d9);
    b = doGG(b, c, d, a, chunk[12], S24, 0x8d2a4c8a);

    // Round 3
    a = doHH(a, b, c, d, chunk[5], S31, 0xfffa3942);
    d = doHH(d, a, b, c, chunk[8], S32, 0x8771f681);
    c = doHH(c, d, a, b, chunk[11], S33, 0x6d9d6122);
    b = doHH(b, c, d, a, chunk[14], S34, 0xfde5380c);
    a = doHH(a, b, c, d, chunk[1], S31, 0xa4beea44);
    d = doHH(d, a, b, c, chunk[4], S32, 0x4bdecfa9);
    c = doHH(c, d, a, b, chunk[7], S33, 0xf6bb4b60);
    b = doHH(b, c, d, a, chunk[10], S34, 0xbebfbc70);
    a = doHH(a, b, c, d, chunk[13], S31, 0x289b7ec6);
    d = doHH(d, a, b, c, chunk[0], S32, 0xeaa127fa);
    c = doHH(c, d, a, b, chunk[3], S33, 0xd4ef3085);
    b = doHH(b, c, d, a, chunk[6], S34, 0x04881d05);
    a = doHH(a, b, c, d, chunk[9], S31, 0xd9d4d039);
    d = doHH(d, a, b, c, chunk[12], S32, 0xe6db99e5);
    c = doHH(c, d, a, b, chunk[15], S33, 0x1fa27cf8);
    b = doHH(b, c, d, a, chunk[2], S34, 0xc4ac5665);

    // Round 4
    a = doII(a, b, c, d, chunk[0], S41, 0xf4292244);
    d = doII(d, a, b, c, chunk[7], S42, 0x432aff97);
    c = doII(c, d, a, b, chunk[14], S43, 0xab9423a7);
    b = doII(b, c, d, a, chunk[5], S44, 0xfc93a039);
    a = doII(a, b, c, d, chunk[12], S41, 0x655b59c3);
    d = doII(d, a, b, c, chunk[3], S42, 0x8f0ccc92);
    c = doII(c, d, a, b, chunk[10], S43, 0xffeff47d);
    b = doII(b, c, d, a, chunk[1], S44, 0x85845dd1);
    a = doII(a, b, c, d, chunk[8], S41, 0x6fa87e4f);
    d = doII(d, a, b, c, chunk[15], S42, 0xfe2ce6e0);
    c = doII(c, d, a, b, chunk[6], S43, 0xa3014314);
    b = doII(b, c, d, a, chunk[13], S44, 0x4e0811a1);
    a = doII(a, b, c, d, chunk[4], S41, 0xf7537e82);
    d = doII(d, a, b, c, chunk[11], S42, 0xbd3af235);
    c = doII(c, d, a, b, chunk[2], S43, 0x2ad7d2bb);
    b = doII(b, c, d, a, chunk[9], S44, 0xeb86d391);

    // Out
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    // Zero sensitive information
    chunk.fill(0);
}

template<std::size_t N>
void
MD5::encode(const std::array<std::uint32_t, N>& input, std::array<std::uint8_t, N * 4>& output)
{
    for (std::size_t i{0}, j{0}; i < N; ++i, j += 4) {
        output[j] = input[i] & 0xFF;
        output[j + 1] = (input[i] >> 8) & 0xFF;
        output[j + 2] = (input[i] >> 16) & 0xFF;
        output[j + 3] = (input[i] >> 24) & 0xFF;
    }
}

template<std::size_t N>
void
MD5::decode(const std::array<std::uint8_t, N * 4>& input, std::array<std::uint32_t, N>& output)
{
    for (std::size_t i{0}, j{0}; i < N; ++i, j += 4) {
        output[i] = static_cast<std::uint32_t>(input[j])
                    | (static_cast<std::uint32_t>(input[j + 1]) << 8)
                    | (static_cast<std::uint32_t>(input[j + 2]) << 16)
                    | (static_cast<std::uint32_t>(input[j + 3]) << 24);
    }
}

} // namespace algorithms