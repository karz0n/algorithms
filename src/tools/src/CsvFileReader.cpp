#include "CsvFileReader.hpp"

#include <sstream>
#include <fstream>

namespace {
bool
getline(std::istream& s, std::string& value)
{
    static const char RC = '\r';
    static const char NL = '\n';
    value.clear();
    while (s.good() && !s.eof()) {
        auto c = std::char_traits<std::string::value_type>::to_char_type(s.get());
        if (c == RC) {
            continue;
        }
        if (c == NL) {
            return true;
        }
        value.push_back(c);
    }
    return !s.eof();
}

bool
getcell(std::istream& s, std::string& value, char delimiter)
{
    static const char DOUBLE_QUOTE = '"';
    value.clear();
    bool ignore{false};
    while (s.good() && !s.eof()) {
        auto c = std::char_traits<std::string::value_type>::to_char_type(s.get());
        if (s.fail() || s.eof()) {
            return true;
        }
        if (c == DOUBLE_QUOTE) {
            ignore = !ignore;
            continue;
        }
        if (c == delimiter && !ignore) {
            return true;
        }
        value.push_back(c);
    }
    return !s.eof();
}
} // namespace

namespace algorithms {

void
CsvFileReader::read(const std::filesystem::path& path, CsvFileHandler& handler)
{
    std::ifstream s{path};
    if (!s) {
        return;
    }
    read(s, handler);
}

void
CsvFileReader::read(const std::string& value, CsvFileHandler& handler)
{
    std::istringstream s{value};
    if (!s) {
        return;
    }
    read(s, handler);
}

void
CsvFileReader::read(std::istream& s, CsvFileHandler& handler)
{
    handler.fileStart();
    std::string line;
    std::size_t lineNo = 0;
    while (getline(s, line)) {
        if (line.empty()) {
            continue;
        }
        if (!handler.lineStart(++lineNo)) {
            continue;
        }
        std::istringstream ss{line};
        std::string cell;
        std::size_t cellNo = 0;
        while (getcell(ss, cell, handler.delimiter())) {
            const bool isLast = ss.eof();
            if (!handler.cell(++cellNo, cell, isLast)) {
                break;
            }
        }
        handler.lineEnd(lineNo);
    }
    handler.fileEnd();
}

} // namespace algorithms
