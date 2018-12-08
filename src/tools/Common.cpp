#include "Common.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std::chrono;

namespace
{
template <typename Container, typename Fn>
void tuple_for_each(const Container& c, Fn fn)
{
    for (auto& e : c) {
        fn(std::get<0>(e), std::get<1>(e), std::get<2>(e));
    }
}
}

namespace algorithms {

std::chrono::nanoseconds measure(std::function<void()> callable)
{
    auto t1 = std::chrono::steady_clock::now();
    callable();
    auto t2 = std::chrono::steady_clock::now();
    return t2 - t1;
}

void printMeasure(const std::string& title, const std::chrono::nanoseconds& time)
{
    std::cout << std::endl;
    std::cout << "Title: " << title << std::endl
              << "Elapsed time: " << formatTime(time) << std::endl;
    std::cout << std::endl;
}

std::string formatTime(nanoseconds time)
{
    using T = std::tuple<nanoseconds, int, const char *>;

    static constexpr T formats[] = {
        T{hours(1), 2, ""},
        T{minutes(1), 2, ":"},
        T{seconds(1), 2, ":"},
        T{milliseconds(1), 3, "."},
        T{microseconds(1), 3, "."}
    };

    std::ostringstream oss;
    tuple_for_each(formats, [&] (auto d, auto w, auto s) {
        oss << s << std::setw(w) << std::setfill('0') << (time / d);
        time %= d;
    });
    return oss.str();
}
} // namespace algorithms
