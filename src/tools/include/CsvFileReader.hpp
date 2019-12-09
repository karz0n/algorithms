#pragma once

#include <istream>
#include <string>
#include <filesystem>

#include "CsvFileHandler.hpp"

namespace algorithms {

class CsvFileReader {
public:
    static void read(const std::filesystem::path& path, CsvFileHandler& handler);

    static void read(const std::string& value, CsvFileHandler& handler);

    static void read(std::istream& stream, CsvFileHandler& handler);
};

} // namespace algorithms
