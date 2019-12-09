#pragma once

#include <string>

namespace algorithms {

class CsvFileHandler {
public:
    static const char DEFAULT_DELIMITER;

    virtual ~CsvFileHandler() = default;

    virtual void fileStart();

    virtual void fileEnd();

    virtual bool lineStart(std::size_t index);

    virtual void lineEnd(std::size_t index);

    virtual bool cell(std::size_t index, const std::string& value, bool isLast);

    virtual char delimiter() const;
};

} // namespace algorithms
