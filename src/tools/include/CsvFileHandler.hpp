#pragma once

#include <string>

namespace algorithms {

class CsvFileHandler {
public:
    static const char DefaultDelimiter;

    virtual ~CsvFileHandler() = default;

    virtual void
    fileStart();

    virtual void
    fileEnd();

    virtual bool
    lineStart(std::size_t index);

    virtual void
    lineEnd(std::size_t index);

    virtual bool
    cell(std::size_t index, const std::string& value, bool isLast);

    [[nodiscard]] virtual char
    delimiter() const;
};

} // namespace algorithms
