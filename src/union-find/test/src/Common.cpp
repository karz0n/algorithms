#include "Common.hpp"

#include <exception>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std::chrono;

namespace {
template<typename Container, typename Fun>
void
tupleForEach(const Container& c, Fun fun)
{
    for (auto& e : c) {
        fun(std::get<0>(e), std::get<1>(e), std::get<2>(e));
    }
}
} // namespace

Unions
readUnionsFromFile(const fs::path& path)
{
    std::ifstream fs(path);
    if (!fs.is_open()) {
        throw std::runtime_error("Open '" + path.string() + "' file");
    }

    try {
        Unions unions;
        std::string buffer;
        if (!std::getline(fs, buffer)) {
            throw std::runtime_error("Read count of unions failed");
        }
        std::size_t size = std::stoul(buffer);
        unions.reserve(size);
        while (std::getline(fs, buffer)) {
            std::istringstream iss(buffer);
            std::size_t p = 0, q = 0;
            iss >> p >> q;
            unions.emplace_back(p, q);
        }
        fs.close();
        return unions;
    } catch (...) {
        fs.close();
        std::throw_with_nested(std::runtime_error("Read unions from '" + path.string() + "' file"));
    }
}

const Unions&
getTinyUnions()
{
    static Unions output = readUnionsFromFile("assets/union-find/tinyUF.txt");
    return output;
}

const Unions&
getMediumUnions()
{
    static Unions output = readUnionsFromFile("assets/union-find/mediumUF.txt");
    return output;
}

const Unions&
getLargeUnions()
{
    static Unions output = readUnionsFromFile("assets/union-find/largeUF.txt");
    return output;
}

nanoseconds
measure(const std::function<void()>& callable)
{
    auto t1 = std::chrono::steady_clock::now();
    callable();
    auto t2 = std::chrono::steady_clock::now();
    return t2 - t1;
}

void
printMeasure(const fs::path& prefix, std::size_t count, const std::chrono::nanoseconds& time)
{
    std::cout << std::endl;
    std::cout << "Processing " << prefix << ":" << std::endl
              << "   elements: " << count << std::endl
              << "   time: " << formatTime(time) << std::endl;
    std::cout << std::endl;
}

std::string
formatTime(nanoseconds time)
{
    using T = std::tuple<nanoseconds, int, const char*>;

    static constexpr T formats[] = {T{hours(1), 2, ""},
                                    T{minutes(1), 2, ":"},
                                    T{seconds(1), 2, ":"},
                                    T{milliseconds(1), 3, "."},
                                    T{microseconds(1), 3, "."}};

    std::ostringstream oss;
    tupleForEach(formats, [&](auto d, auto w, auto s) {
        oss << s << std::setw(w) << std::setfill('0') << (time / d);
        time %= d;
    });
    return oss.str();
}
