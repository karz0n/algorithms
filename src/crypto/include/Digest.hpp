#pragma once

#include <string>
#include <vector>

namespace algorithms {

class Digest {
public:
    Digest() = default;

    explicit Digest(const std::string& str);

    explicit Digest(const void* data, std::size_t length);

    const std::uint8_t&
    operator[](std::size_t index) const;

    explicit operator bool() const;

    bool
    operator!() const;

    [[nodiscard]] std::size_t
    size() const;

    [[nodiscard]] bool
    empty() const;

    [[nodiscard]] std::string
    toString(bool upperCase = false) const;

    void
    fromString(const std::string& str);

    void
    copyTo(void* dst, std::size_t size) const;

    void
    copyFrom(const void* src, std::size_t size);

    void
    swap(Digest&);

    void
    clear();

    friend std::ostream&
    operator<<(std::ostream& stream, const Digest&);

    friend std::istream&
    operator>>(std::istream& stream, Digest&);

private:
    std::vector<std::uint8_t> _data;
};

} // namespace algorithms