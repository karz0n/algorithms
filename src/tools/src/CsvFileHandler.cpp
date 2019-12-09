#include "CsvFileHandler.hpp"

namespace algorithms {
const char CsvFileHandler::DEFAULT_DELIMITER = ',';

void
CsvFileHandler::fileStart()
{
}

void
CsvFileHandler::fileEnd()
{
}

bool
CsvFileHandler::lineStart(std::size_t)
{
    return true;
}

void
CsvFileHandler::lineEnd(std::size_t)
{
}

bool
CsvFileHandler::cell(std::size_t, const std::string&, bool)
{
    return true;
}

char
CsvFileHandler::delimiter() const
{
    return DEFAULT_DELIMITER;
}
} // namespace algorithms
