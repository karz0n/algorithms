#include "UUID.hpp"

#include "ByteOrder.hpp"
#include "MD5.hpp"
#include "SHA1.hpp"

#include <iomanip>
#include <sstream>
#include <random>
#include <chrono>

#include <cstring>

namespace algorithms {

UUID::UUID()
    : _timeLo{}
    , _timeMi{}
    , _timeHi{}
    , _seqres{}
    , _node{}
{
    _node.fill(0);
}

UUID::UUID(std::uint32_t lo,
           std::uint16_t mi,
           std::uint16_t hi,
           std::uint16_t seqres,
           const NodeArray& node)
    : _timeLo{lo}
    , _timeMi{mi}
    , _timeHi{hi}
    , _seqres{seqres}
    , _node{node}
{
}

UUID::UUID(const void* container, Version version)
    : UUID{}
{
    copyFrom(container);

    _timeHi &= 0x0FFF;
    _timeHi |= (static_cast<int>(version) << 12);
    _seqres &= 0x3FFF;
    _seqres |= 0x8000;
}

UUID::UUID(const std::string& str)
    : UUID{}
{
    fromString(str);
}

UUID::UUID(const void* container)
    : UUID{}
{
    copyFrom(container);
}

void
UUID::reset()
{
    _timeLo = 0;
    _timeMi = 0;
    _timeHi = 0;
    _seqres = 0;

    _node.fill(0);
}

void
UUID::swap(UUID& other)
{
    if (this != &other) {
        std::swap(_timeLo, other._timeLo);
        std::swap(_timeMi, other._timeMi);
        std::swap(_timeHi, other._timeHi);
        std::swap(_seqres, other._seqres);
        std::swap(_node, other._node);
    }
}

bool
UUID::isNull() const
{
    return (compare(null()) == 0);
}

UUID::Version
UUID::version() const
{
    return Version(_seqres >> 12);
}

std::string
UUID::toString(bool upperCase /*= false*/) const
{
    std::ostringstream stream;
    if (upperCase) {
        stream.setf(std::ios::uppercase);
    }
    stream << *this;
    return stream.str();
}

void
UUID::fromString(const std::string& str)
{
    std::istringstream(str) >> *this;
}

void
UUID::copyTo(void* container) const
{
    if (!container) {
        throw std::invalid_argument{"Invalid pointer value"};
    }

    auto* castData = static_cast<std::uint8_t*>(container);
    const std::uint32_t i32 = ByteOrder::convert(_timeLo, std::endian::native, std::endian::big);
    std::memcpy(castData, &i32, sizeof i32);
    castData += sizeof(i32);
    std::uint16_t i16 = ByteOrder::convert(_timeMi, std::endian::native, std::endian::big);
    std::memcpy(castData, &i16, sizeof(i16));
    castData += sizeof(i16);
    i16 = ByteOrder::convert(_timeHi, std::endian::native, std::endian::big);
    std::memcpy(castData, &i16, sizeof(i16));
    castData += sizeof(i16);
    i16 = ByteOrder::convert(_seqres, std::endian::native, std::endian::big);
    std::memcpy(castData, &i16, sizeof(i16));
    castData += sizeof(i16);
    std::memcpy(castData, _node.data(), _node.size());
}

void
UUID::copyFrom(const void* container)
{
    if (!container) {
        throw std::invalid_argument{"Invalid pointer value"};
    }

    const auto* castData = static_cast<const std::uint8_t*>(container);
    std::memcpy(&_timeLo, castData, sizeof _timeLo);
    _timeLo = ByteOrder::convert(_timeLo, std::endian::big, std::endian::native);
    castData += sizeof _timeLo;
    std::memcpy(&_timeMi, castData, sizeof _timeMi);
    _timeMi = ByteOrder::convert(_timeMi, std::endian::big, std::endian::native);
    castData += sizeof _timeMi;
    std::memcpy(&_timeHi, castData, sizeof _timeHi);
    _timeHi = ByteOrder::convert(_timeHi, std::endian::big, std::endian::native);
    castData += sizeof _timeHi;
    std::memcpy(&_seqres, castData, sizeof _seqres);
    _seqres = ByteOrder::convert(_seqres, std::endian::big, std::endian::native);
    castData += sizeof _seqres;
    std::memcpy(_node.data(), castData, _node.size());
}

UUID
UUID::createByTime()
{
    static thread_local std::uint64_t timestamp{0};
    static thread_local std::uint16_t sequence{0};

    static const thread_local NodeArray node = getRandomNode();

    const std::uint64_t now{getTimestamp()};
    if (now <= timestamp) {
        sequence++;
    }
    timestamp = now;

    const auto timeLo = static_cast<std::uint32_t>(timestamp & 0xFFFFFFFF);
    const auto timeMi = static_cast<std::uint16_t>((timestamp >> 32) & 0xFFFF);
    const auto timeHi = static_cast<std::uint16_t>(
        (timestamp >> 48) & 0x0FFF + (static_cast<std::uint16_t>(Version::TimeBased) << 12));
    const auto seqres = static_cast<std::uint16_t>((sequence & 0x3FFF) | 0x8000);

    return UUID{timeLo, timeMi, timeHi, seqres, node};
}

UUID
UUID::createByName(const UUID& ns, const std::string& name)
{
    MD5 method;
    return createByName(ns, name, method);
}

UUID
UUID::createByName(const UUID& ns, const std::string& name, DigestMethod& method)
{
    Version version{Version::NameBased};
    if (dynamic_cast<SHA1*>(&method)) {
        version = Version::NameBasedSHA1;
    }

    const std::size_t size{method.length()};
    std::unique_ptr<std::uint8_t[]> buffer(new uint8_t[size]);
    ns.copyTo(buffer.get());
    method.reset();
    method.update(buffer.get(), Size);
    method.update(name.data(), name.length());
    const auto digest = method.finalize();
    digest.copyTo(buffer.get(), size);

    return UUID{buffer.get(), version};
}

UUID
UUID::createByRandom()
{
    std::mt19937_64 random(getTimestamp());

    std::uniform_int_distribution<std::uint64_t> uniform64;
    const std::uint64_t n64 = uniform64(random);
    std::uniform_int_distribution<uint16_t> uniform16;
    const std::uint16_t n16 = uniform16(random);

    const auto timeLo = static_cast<std::uint32_t>(n64 & 0xFFFFFFFF);
    const auto timeMi = static_cast<std::uint16_t>((n64 >> 32) & 0xFFFF);
    const auto timeHi = static_cast<std::uint16_t>(
        (n64 >> 48) & 0x0FFF + (static_cast<std::uint16_t>(Version::TimeBased) << 12));
    const auto seqres = static_cast<std::uint16_t>((n16 & 0x3FFF) | 0x8000);

    return UUID{timeLo, timeMi, timeHi, seqres, getRandomNode()};
}

const UUID&
UUID::null()
{
    static const UUID output;
    return output;
}

const UUID&
UUID::dns()
{
    static const UUID output(
        0x6ba7b810, 0x9dad, 0x11d1, 0x80b4, {0x00, 0xC0, 0x4f, 0xd4, 0x30, 0xc8});
    return output;
}

const UUID&
UUID::uri()
{
    static const UUID output(
        0x6ba7b811, 0x9dad, 0x11d1, 0x80b4, {0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8});
    return output;
}

const UUID&
UUID::oid()
{
    static const UUID output(
        0x6ba7b812, 0x9dad, 0x11d1, 0x80b4, {0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8});
    return output;
}

const UUID&
UUID::x500()
{
    static const UUID output(
        0x6ba7b814, 0x9dad, 0x11d1, 0x80b4, {0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8});
    return output;
}

int
UUID::compare(const UUID& other) const
{
    if (_timeLo != other._timeLo) {
        return (_timeLo > other._timeLo) ? +1 : -1;
    }
    if (_timeMi != other._timeMi) {
        return (_timeMi > other._timeMi) ? +1 : -1;
    }
    if (_timeHi != other._timeHi) {
        return (_timeHi > other._timeHi) ? +1 : -1;
    }
    if (_seqres != other._seqres) {
        return (_seqres > other._seqres) ? +1 : -1;
    }

    for (std::size_t i{0}; i < _node.size(); ++i) {
        if (_node[i] < other._node[i]) {
            return -1;
        }
        if (_node[i] > other._node[i]) {
            return +1;
        }
    }

    return 0;
}

const UUID::NodeArray&
UUID::getRandomNode()
{
    static thread_local NodeArray node{};
    std::mt19937_64 random(getTimestamp());
    std::uniform_int_distribution<std::uint64_t> uniform(0, 0xFFFFFFFFFFFF);
    const std::uint64_t value = ByteOrder::convert(
        uniform(random) & 0x01FFFFFFFFFF, std::endian::native, std::endian::little);
    std::memcpy(node.data(), &value, node.size());
    return node;
}

std::uint64_t
UUID::getTimestamp()
{
    using Ratio = std::ratio<1, 10000000>;
    using Duration = std::chrono::duration<std::uint64_t, Ratio>;

    static thread_local uint32_t counter{0};
    static thread_local uint64_t lastCount{0};
    std::uint64_t count;
    while (true) {
        const auto duration{std::chrono::steady_clock::now().time_since_epoch()};
        count = std::chrono::duration_cast<Duration>(duration).count();
        count += uint64_t(1000 * 1000 * 10) * uint64_t(60 * 60 * 24)
                 * uint64_t(17 + 30 + 31 + 365 + 387);
        if (count != lastCount) {
            lastCount = count;
            counter = 0;
            break;
        }
        if (counter < count) {
            counter++;
            break;
        }
    }
    return (count + counter);
}

std::ostream&
operator<<(std::ostream& stream, const UUID& uuid)
{
    std::ostringstream oss;
    oss.copyfmt(stream);
    oss.setf(std::ios::hex, std::ios::basefield);
    oss.fill(oss.widen('0'));
    oss << std::setw(8) << uuid._timeLo << '-';
    oss << std::setw(4) << uuid._timeMi << '-';
    oss << std::setw(4) << uuid._timeHi << '-';
    oss << std::setw(4) << uuid._seqres << '-';
    for (const int byte : uuid._node) {
        oss << std::setw(2) << byte;
    }
    stream << oss.str();
    return stream;
}

std::istream&
operator>>(std::istream& stream, UUID& uuid)
{
    std::string buffer;
    stream >> buffer;
    if (buffer.size() != UUID::CharCount) {
        throw std::length_error{"Invalid size of input UUID"};
    }
    if (buffer[8] != '-' || buffer[13] != '-' || buffer[18] != '-' || buffer[23] != '-') {
        throw std::invalid_argument{"Invalid format of input UUID"};
    }

    std::istringstream iss(buffer);
    iss >> std::setw(8) >> buffer;
    uuid._timeLo = std::stoul(buffer, nullptr, 16);
    iss.ignore();
    iss >> std::setw(4) >> buffer;
    uuid._timeMi = std::stoi(buffer, nullptr, 16);
    iss.ignore();
    iss >> std::setw(4) >> buffer;
    uuid._timeHi = std::stoi(buffer, nullptr, 16);
    iss.ignore();
    iss >> std::setw(4) >> buffer;
    uuid._seqres = std::stoi(buffer, nullptr, 16);
    iss.ignore();
    for (auto& byte : uuid._node) {
        iss >> std::setw(2) >> buffer;
        byte = std::stoi(buffer, nullptr, 16);
    }

    return stream;
}

} // namespace algorithms