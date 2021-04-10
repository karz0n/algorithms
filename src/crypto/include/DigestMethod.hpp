#pragma once

#include <string>
#include <string_view>

namespace algorithms {

class DigestMethod {
public:
    DigestMethod() = default;

    virtual ~DigestMethod() = default;

    virtual void
    reset()
        = 0;

    void
    update(const std::string& data);

    void
    update(const std::string_view& data);

    virtual void
    update(const void* data, std::size_t size)
        = 0;

    [[nodiscard]] virtual Digest
    finalize()
        = 0;

    [[nodiscard]] virtual std::size_t
    length() const = 0;

    Digest
    operator()(const std::string& data);

    Digest
    operator()(const std::string_view& data);

    Digest
    operator()(const void* data, std::size_t size);

public:
    DigestMethod(const DigestMethod&) = delete;

    DigestMethod&
    operator=(const DigestMethod&)
        = delete;
};

//
// Inlines
//

inline void
DigestMethod::update(const std::string& data)
{
    update(data.data(), data.size());
}

inline void
DigestMethod::update(const std::string_view& data)
{
    update(data.data(), data.size());
}

inline Digest
DigestMethod::operator()(const std::string& data)
{
    update(data);
    return finalize();
}

inline Digest
DigestMethod::operator()(const std::string_view& data)
{
    update(data);
    return finalize();
}

inline Digest
DigestMethod::operator()(const void* data, std::size_t size)
{
    update(data, size);
    return finalize();
}

} // namespace algorithms