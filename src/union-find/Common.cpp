#include "Common.hpp"

#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>

namespace algorithms
{
namespace uf
{

Unions readUnionsFromFile(const std::string& path)
{
    std::ifstream fs(path);
    if (!fs.is_open()) {
        throw std::runtime_error("Open '" + path + "' file");
    }

    try {
        Unions unions;
        std::string buffer;
        if (std::getline(fs, buffer)) {
            std::size_t size = std::stoul(buffer);
            unions.reserve(size);
        }
        else {
            throw std::runtime_error("Read size");
        }
        while(std::getline(fs, buffer)) {
            std::istringstream ss(buffer);
            std::size_t p = 0, q = 0;
            ss >> p >> q;
            unions.emplace_back(std::make_pair(p, q));
        }
        fs.close();
        return unions;
    } catch (...) {
        fs.close();
        std::throw_with_nested(
            std::runtime_error("Read unions from '" + path + "' file"));
    }
}

void run(std::function<void()> callable)
{
    auto t1 = std::chrono::steady_clock::now();
    callable();
    auto t2 = std::chrono::steady_clock::now();

    auto diff = t2 - t1;
    std::cout << "Elapsed time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
              << " milliseconds ("
              << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()
              << " nanoseconds)"
              << std::endl;
}

} // namespace uf
} // namespace algorithms




