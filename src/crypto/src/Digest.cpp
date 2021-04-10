#include "Digest.hpp"

#include <iomanip>
#include <sstream>

#include <cstring>

namespace algorithms {

Digest::Digest(const std::string& str)
{
    fromString(str);
}

Digest::Digest(const void* data, size_t length)
{
    copyFrom(data, length);
}

const std::uint8_t&
Digest::operator[](std::size_t index) const
{
    return _data[index];
}

Digest::operator bool() const
{
    return !empty();
}

inline bool
Digest::operator!() const
{
    return empty();
}

std::size_t
Digest::size() const
{
    return _data.size();
}

bool
Digest::empty() const
{
    return _data.empty();
}

std::string
Digest::toString(bool upperCase) const
{
    std::ostringstream stream;
    if (upperCase) {
        stream.setf(std::ios::uppercase);
    }
    stream << *this;
    return stream.str();
}

void
Digest::fromString(const std::string& str)
{
    std::istringstream(str) >> *this;
}

void
Digest::copyTo(void* dst, std::size_t size) const
{
    if (!empty()) {
        return;
    }

    if (!dst || _data.size() > size) {
        throw std::invalid_argument{"Invalid pointer value or container size"};
    }

    std::memcpy(dst, _data.data(), _data.size());
}

void
Digest::copyFrom(const void* src, std::size_t size)
{
    if (!src) {
        throw std::invalid_argument{"Invalid pointer value"};
    }

    if (size == 0) {
        clear();
    } else {
        _data.resize(size);
        std::memcpy(_data.data(), src, size);
    }
}

void
Digest::swap(Digest& other)
{
    _data.swap(other._data);
}

void
Digest::clear()
{
    _data.clear();
}

std::ostream&
operator<<(std::ostream& stream, const Digest& digest)
{
    if (!digest) {
        return stream;
    }

    std::ostringstream oss;
    oss.copyfmt(stream);
    oss.setf(std::ios::hex, std::ios::basefield);
    oss.fill(oss.widen('0'));
    for (const auto byte : digest._data) {
        oss << std::setw(2) << static_cast<int>(byte);
    }
    stream << oss.str();

    return stream;
}

std::istream&
operator>>(std::istream& stream, Digest& digest)
{
    digest.clear();

    std::string str;
    stream >> str;
    if (str.empty()) {
        return stream;
    }

    const auto size = str.size();
    if (size % 2 != 0) {
        throw std::length_error{"Invalid digest length"};
    }
    digest._data.reserve(size / 2);

    std::istringstream iss(str);
    while (iss) {
        iss >> std::setw(2) >> str;
        if (iss) {
            const std::uint8_t byte = std::stoi(str, nullptr, 16);
            digest._data.push_back(byte);
        }
    }

    return stream;
}

} // namespace algorithms