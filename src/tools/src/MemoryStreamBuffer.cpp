#include "MemoryStreamBuffer.hpp"

namespace algorithms {

MemoryStreamBuffer::MemoryStreamBuffer(std::size_t initialSize)
    : _blob(initialSize)
{
    const auto beg = _blob.data();
    const auto end = _blob.data() + initialSize;

    setp(beg, end);
    setg(beg, beg, end);
}

MemoryStreamBuffer::MemoryStreamBuffer(Blob bytes)
    : _blob(std::move(bytes))
{
    const auto beg = _blob.data();
    const auto end = _blob.data() + _blob.size();

    setp(beg, end);
    setg(beg, beg, end);
}

std::size_t
MemoryStreamBuffer::size() const
{
    return _blob.size();
}

bool
MemoryStreamBuffer::empty() const
{
    return _blob.empty();
}

std::streamsize
MemoryStreamBuffer::available(std::ios_base::openmode mode) const
{
    std::streamsize output{0};
    if (size() > 0) {
        if (mode == std::ios_base::out) {
            return epptr() - pptr();
        }
        if (mode == std::ios_base::in) {
            return egptr() - gptr();
        }
    }
    return output;
}

std::streamsize
MemoryStreamBuffer::tell(std::ios_base::openmode mode) const
{
    if (mode == std::ios_base::out) {
        return pptr() - pbase();
    }
    if (mode == std::ios_base::in) {
        return gptr() - eback();
    }
    return -1;
}

void
MemoryStreamBuffer::put(const DynamicBitSet& bits)
{
    if (bits.empty()) {
        return;
    }

    std::byte value{0};
    for (std::size_t n{0}, mod{0}; n < bits.size(); ++n, mod = n % DynamicBitSet::BitsInByte) {
        if (n > 0 && mod == 0) {
            sputc(static_cast<std::uint8_t>(value));
            value = std::byte{0};
        }
        if (bits[n]) {
            value = value | (std::byte{0b1} << mod);
        }
    }
    sputc(static_cast<std::uint8_t>(value));
}

std::size_t
MemoryStreamBuffer::get(DynamicBitSet& bits, std::size_t count)
{
    std::size_t bitsRead{0};

    const std::size_t bytesCount{count / DynamicBitSet::BitsInByte};
    std::streamsize bytesAvail{available(std::ios_base::in)};
    for (std::size_t n{0}; n < bytesCount && bytesAvail > 0; ++n, --bytesAvail) {
        bits.putBits(sbumpc(), DynamicBitSet::BitsInByte);
        bitsRead += DynamicBitSet::BitsInByte;
    }

    const std::size_t bitsCount{count % DynamicBitSet::BitsInByte};
    if (bitsCount > 0 && bytesAvail > 0) {
        bits.putBits(sbumpc(), bitsCount);
        bitsRead += bitsCount;
    }

    return bitsRead;
}

MemoryStreamBuffer::Blob
MemoryStreamBuffer::extract()
{
    const std::streamsize count = tell(std::ios_base::out);
    if (count == 0) {
        return {};
    }

    Blob blob(InitialSize);
    _blob.resize(count);
    _blob.swap(blob);
    const auto beg = _blob.data();
    const auto end = _blob.data() + _blob.size();
    setp(beg, end);
    setg(beg, beg, end);
    return blob;
}

MemoryStreamBuffer::int_type
MemoryStreamBuffer::overflow(int_type ch)
{
    if (!traits_type::eq_int_type(ch, traits_type::eof())) {
        resize(size() * 2);
        sputc(traits_type::to_char_type(ch));
    }
    return traits_type::not_eof(ch);
}

MemoryStreamBuffer::pos_type
MemoryStreamBuffer::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode mode)
{
    pos_type retVal{off_type{-1}};

    const bool pTest = (mode & std::ios_base::in) != 0;
    const bool gTest = (mode & std::ios_base::out) != 0;
    if (pTest && gTest && dir == std::ios_base::cur) {
        return retVal;
    }

    off_type pOffset{off};
    off_type gOffset{off};
    if (dir == std::ios_base::end) {
        pOffset += size();
        gOffset += size();
    }
    else if (dir == std::ios_base::cur) {
        pOffset += pptr() - pbase();
        gOffset += gptr() - eback();
    }

    if (pTest && pOffset > 0 && pOffset <= size()) {
        setp(pbase(), epptr());
        pbump(pOffset);
        retVal = pOffset;
    }
    if (gTest && gOffset > 0 && gOffset <= size()) {
        setg(eback(), eback() + gOffset, egptr());
        retVal = gOffset;
    }

    return retVal;
}

MemoryStreamBuffer::pos_type
MemoryStreamBuffer::seekpos(pos_type pos, std::ios_base::openmode mode)
{
    pos_type retVal{off_type{-1}};

    const bool pTest = (mode & std::ios_base::in) != 0;
    const bool gTest = (mode & std::ios_base::out) != 0;

    const bool valid = (pos >= 0) && (pos <= egptr() - pbase());
    if (valid) {
        if (pTest) {
            seekoff(pos, std::ios_base::beg, std::ios_base::out);
        }
        if (gTest) {
            seekoff(pos, std::ios_base::beg, std::ios_base::in);
        }
        retVal = pos;
    }

    return retVal;
}

void
MemoryStreamBuffer::resize(std::size_t newSize)
{
    const auto pOffset = tell(std::ios_base::out);
    const auto gOffset = tell(std::ios_base::in);

    _blob.resize(newSize);

    const auto beg = _blob.data();
    const auto end = _blob.data() + _blob.size();
    setp(beg, end);
    setg(beg, beg, end);

    seekpos(pOffset, std::ios_base::out);
    seekpos(gOffset, std::ios_base::in);
}

} // namespace algorithms