#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <CsvFileReader.hpp>

using namespace algorithms;

using testing::_;
using testing::Return;
using testing::Gt;

static const std::string VALUE = R"(
    004,AF,AFG,Afghanistan,Kabul
    008,AL,ALB,Albania,Tirana
)";

class MockFileHandler : public CsvFileHandler {
public:
    MOCK_METHOD(void, fileStart, (), (override));
    MOCK_METHOD(void, fileEnd, (), (override));
    MOCK_METHOD(bool, lineStart, (std::size_t), (override));
    MOCK_METHOD(void, lineEnd, (std::size_t), (override));
    MOCK_METHOD(bool, cell, (std::size_t, const std::string&, bool), (override));

    char delimiter() const override
    {
        return ',';
    }
};

TEST(Test, PositiveTest)
{
    MockFileHandler handler;

    ON_CALL(handler, lineStart(_))
        .WillByDefault(Return(true));
    ON_CALL(handler, cell(_, _, _))
        .WillByDefault(Return(true));

    EXPECT_CALL(handler, fileStart())
        .Times(1);
    EXPECT_CALL(handler, fileEnd())
        .Times(1);
    EXPECT_CALL(handler, lineStart(Gt(0)))
        .Times(2);
    EXPECT_CALL(handler, lineEnd(Gt(0)))
        .Times(2);
    EXPECT_CALL(handler, cell(Gt(0), _, _))
        .Times(10);

    CsvFileReader::read(VALUE, handler);
}
