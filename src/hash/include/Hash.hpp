#pragma once

#include <string>
#include <cstring>

namespace algorithms {

template<typename T>
struct hash {
    std::size_t
    operator()(const T&) const
    {
        return 0;
    }
};

template<>
struct hash<int> {
    std::size_t
    operator()(int input)
    {
        return input;
    }
};

template<>
struct hash<bool> {
    std::size_t
    operator()(bool input)
    {
        return input ? 1231 : 1237;
    }
};

template<>
struct hash<std::string> {
    std::size_t
    operator()(const std::string& input) const
    {
        std::size_t output{0};
        for (std::size_t i = 0; i < input.size(); ++i) {
            output = input[i] + (31 * output);
        }
        return output;
    }
};

template<>
struct hash<double> {
    /** Bit mask to isolate the exponent field */
    static inline std::uint64_t EXP_BIT_MASK = 0x7ff0000000000000ul;
    /** Bit mask to isolate the significand field */
    static inline std::uint64_t SIGN_BIT_MASK = 0x8000000000000000ul;

    std::size_t
    operator()(double input) const
    {
        std::uint64_t bits = doubleToBits(input);
        return std::size_t(bits ^ (bits >> 32));
    }

private:
    static std::uint64_t
    doubleToBits(double input)
    {
        std::uint64_t bits = doubleToRawBits(input);
        if ((bits & EXP_BIT_MASK) == EXP_BIT_MASK && (bits & SIGN_BIT_MASK) != 0ul) {
            return 0x7ff8000000000000ul;
        }
        return bits;
    }

    static std::uint64_t
    doubleToRawBits(double input)
    {
        std::uint64_t output{0};
        std::memcpy(&output, &input, sizeof output);
        return output;
    }
};

template<typename T>
void
combine(std::size_t& seed, const T& value)
{
    seed = 31 * seed + hash<T>{}(value);
}

template<typename... Args>
std::size_t
combine(const Args&... args)
{
    std::size_t seed{17};
    (... , combine(seed, args));
    return seed;
}

} // namespace algorithms
