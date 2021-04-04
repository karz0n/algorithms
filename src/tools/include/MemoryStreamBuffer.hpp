#pragma once

#include <streambuf>

#include "DynamicBitSet.hpp"

namespace algorithms {

class MemoryStreamBuffer : public std::basic_streambuf<std::uint8_t> {
public:
    static constexpr std::size_t InitialSize = 256;

    using Blob = std::vector<std::uint8_t>;

    explicit MemoryStreamBuffer(std::size_t initialSize = InitialSize);

    explicit MemoryStreamBuffer(Blob blob);

    [[nodiscard]] std::size_t
    size() const;

    [[nodiscard]] bool
    empty() const;

    [[nodiscard]] std::streamsize
    available(std::ios_base::openmode mode) const;

    [[nodiscard]] std::streamsize
    tell(std::ios_base::openmode mode) const;

    void
    put(const DynamicBitSet& bits);

    std::size_t
    get(DynamicBitSet& bits, std::size_t count);

    [[nodiscard]] Blob
    extract();

private:
    int_type
    overflow(int_type ch) override;

    pos_type
    seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode mode) override;

    pos_type
    seekpos(pos_type pos, std::ios_base::openmode mode) override;

private:
    void
    resize(std::size_t newSize);

private:
    Blob _blob;
};

} // namespace algorithms
