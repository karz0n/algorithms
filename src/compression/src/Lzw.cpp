#include "Lzw.hpp"

#include "DynamicBitSet.hpp"
#include "MemoryStreamBuffer.hpp"
#include "TernarySearchTries.hpp"

#include <array>

#include <cstddef>

namespace algorithms::lzw {

struct LzwHeader {
    std::uint32_t dataBits{0};
};

bool
read(MemoryStreamBuffer& buffer, LzwHeader& header)
{
    auto b1 = buffer.sbumpc();
    auto b2 = buffer.sbumpc();
    auto b3 = buffer.sbumpc();
    if (b1 != 'L' || b2 != 'Z' || b3 != 'W') {
        return false;
    }

    const std::size_t count = sizeof(header);
    if (buffer.sgetn(reinterpret_cast<std::uint8_t*>(&header), count) != count) {
        return false;
    }
    return true;
}

bool
read(MemoryStreamBuffer& buffer, DynamicBitSet& bits, std::size_t count)
{
    return (buffer.get(bits, count) == count);
}

void
write(MemoryStreamBuffer& buffer, const LzwHeader& header)
{
    buffer.sputc('L');
    buffer.sputc('Z');
    buffer.sputc('W');
    buffer.sputn(reinterpret_cast<const std::uint8_t*>(&header), sizeof(header));
}

void
write(MemoryStreamBuffer& buffer, const DynamicBitSet& bits)
{
    buffer.put(bits);
}

Bytes
encode(std::string_view input)
{
    TernarySearchTries tst;
    for (std::size_t n{0}; n < R; ++n) {
        const std::string value{std::string::traits_type::to_char_type(n)};
        tst.put(value, n);
    }
    std::size_t code = R + 1;

    DynamicBitSet bitSet;
    while (!input.empty()) {
        const auto prefix = tst.longestPrefixOf(input);
        bitSet.putBits(tst.get(prefix), W);

        const auto len{prefix.size()};
        if (len < input.size() && code < L) {
            tst.put(input.substr(0, len + 1), code++);
        }

        input = input.substr(len);
    }
    bitSet.putBits(R, W);

    LzwHeader header;
    header.dataBits = bitSet.size();

    MemoryStreamBuffer buffer;
    write(buffer, header);
    write(buffer, bitSet);
    return buffer.extract();
}

std::string
decode(Bytes bytes)
{
    MemoryStreamBuffer buffer{std::move(bytes)};
    LzwHeader header;
    if (!read(buffer, header)) {
        return {};
    }

    DynamicBitSet dataBits;
    if (!read(buffer, dataBits, header.dataBits)) {
        return {};
    }
    dataBits = dataBits.reverse();

    std::array<std::string, L> st;
    std::size_t n{0};
    for (; n < R; ++n) {
        st[n] = std::string{std::string::traits_type::to_char_type(n)};
    }
    st[n++] = "";

    std::size_t codeword = dataBits.popBits(W, std::endian::little);
    if (codeword == R) {
        return {};
    }

    std::string accum;
    std::string value = st[codeword];
    while (!dataBits.empty()) {
        accum += value;

        codeword = dataBits.popBits(W, std::endian::little);
        if (codeword == R) {
            break;
        }

        auto s = st[codeword];
        if (n == codeword) {
            // Trick for cases when codeword is absent
            s = value + value[0];
        }

        if (n < L) {
            // Preserve new association codeword and sequence of chars
            st[n++] = value + s[0];
        }

        value = s;
    }
    return accum;
}

} // namespace algorithms::lzw