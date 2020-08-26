#pragma once

#include <chrono>
#include <vector>
#include <utility>
#include <functional>
#include <filesystem>

namespace fs = std::filesystem;

using Union = std::pair<std::size_t, std::size_t>;
using Unions = std::vector<Union>;

Unions
readUnionsFromFile(const fs::path& path);

const Unions&
getTinyUnions();

const Unions&
getMediumUnions();

const Unions&
getLargeUnions();

std::chrono::nanoseconds
measure(const std::function<void()>& callable);

void
printMeasure(const fs::path& prefix, std::size_t count, const std::chrono::nanoseconds& time);

std::string
formatTime(std::chrono::nanoseconds time);

template<typename T>
static T
makeSet(const std::string& prefix, const Unions& unions)
{
    T output;
    auto time = measure([&]() {
        output.reset(unions.size());
        for (const auto& u : unions) {
            if (!output.connected(u.first, u.second)) {
                output.associate(u.first, u.second);
            }
        }
    });
    printMeasure(prefix, unions.size(), time);
    return output;
}
