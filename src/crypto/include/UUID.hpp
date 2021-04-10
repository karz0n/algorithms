#pragma once

#include "Digest.hpp"
#include "DigestMethod.hpp"

#include <array>
#include <string>

namespace algorithms {

class UUID final {
public:
    /** The size of UUID in bytes */
    static constexpr unsigned Size = 16;

    enum class Version : std::uint32_t {
        TimeBased = 0x01,
        Dce = 0x02,
        NameBased = 0x03,
        Random = 0x04,
        NameBasedSHA1 = 0x05
    };

    UUID();

    explicit UUID(const std::string& str);

    explicit UUID(const void* container);

    [[nodiscard]] std::string
    toString(bool upperCase = false) const;

    void
    fromString(const std::string& str);

    void
    copyTo(void* container) const;

    void
    copyFrom(const void* container);

    void
    reset();

    void
    swap(UUID&);

    [[nodiscard]] bool
    isNull() const;

    [[nodiscard]] Version
    version() const;

    friend std::ostream&
    operator<<(std::ostream& stream, const UUID&);

    friend std::istream&
    operator>>(std::istream& stream, UUID&);

public: /** Factory Methods */
    static UUID
    createByTime();

    static UUID
    createByName(const UUID& ns, const std::string& name);

    static UUID
    createByName(const UUID& ns, const std::string& name, DigestMethod& method);

    static UUID
    createByRandom();

public: /** Namespaces */
    static const UUID&
    null();

    static const UUID&
    dns();

    static const UUID&
    uri();

    static const UUID&
    oid();

    static const UUID&
    x500();

private:
    static constexpr unsigned NodeBytes = 6;
    static constexpr unsigned CharCount = Size * 2 + 4;

    using NodeArray = std::array<std::uint8_t, NodeBytes>;

    explicit UUID(const void* container, Version version);

    explicit UUID(std::uint32_t lo, std::uint16_t mi, std::uint16_t hi, std::uint16_t seqres, const NodeArray& node);

    [[nodiscard]] int
    compare(const UUID& other) const;

    static const NodeArray&
    getRandomNode();

    static std::uint64_t
    getTimestamp();

private:
    std::uint32_t _timeLo;
    std::uint16_t _timeMi;
    std::uint16_t _timeHi;
    std::uint16_t _seqres;
    NodeArray _node;
};

} // namespace algorithms