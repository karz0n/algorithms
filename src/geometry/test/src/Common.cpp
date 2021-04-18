#include "Common.hpp"

#include <fstream>

void
read(const std::filesystem::path& path, algorithms::Points& points)
{
    std::ifstream s{path};
    if (!s) {
        throw std::runtime_error{"Failed to open file"};
    }

    std::size_t count{};

    s >> count;
    if (!s) {
        throw std::runtime_error{"Failed to read number of vertices or it's invalid"};
    }

    points.clear();
    points.reserve(count);

    for (std::string line; std::getline(s, line);) {
        if (line.empty()) {
            continue;
        }

        std::stringstream lineS{line};
        std::size_t x{};
        std::size_t y{};
        lineS >> x >> y;
        if (!lineS) {
            throw std::logic_error{"End of stream"};
        }

        points.emplace_back(x, y);
    }
}