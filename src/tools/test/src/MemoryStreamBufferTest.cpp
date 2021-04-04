#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MemoryStreamBuffer.hpp"

using namespace testing;
using namespace algorithms;

TEST(MemoryStreamBuffer, Write)
{
    MemoryStreamBuffer buffer;

    EXPECT_EQ(buffer.tell(std::ios_base::out), 0);
    EXPECT_EQ(buffer.tell(std::ios_base::in), 0);

    buffer.sputc('A');
    buffer.sputc('B');
    buffer.sputc('C');

    EXPECT_NE(buffer.tell(std::ios_base::out), 0);
    EXPECT_EQ(buffer.tell(std::ios_base::in), 0);

    EXPECT_EQ(buffer.sbumpc(), 'A');
    EXPECT_EQ(buffer.sbumpc(), 'B');
    EXPECT_EQ(buffer.sbumpc(), 'C');

    EXPECT_NE(buffer.tell(std::ios_base::out), 0);
    EXPECT_NE(buffer.tell(std::ios_base::in), 0);
}

TEST(MemoryStreamBuffer, Grow)
{
    static const std::size_t InitialSize{3U};

    MemoryStreamBuffer buffer{InitialSize};

    EXPECT_THAT(buffer.size(), Eq(InitialSize));

    buffer.sputc('A');
    buffer.sputc('B');
    buffer.sputc('C');
    buffer.sputc('D');

    EXPECT_THAT(buffer.size(), Gt(InitialSize));

    EXPECT_EQ(buffer.sbumpc(), 'A');
    EXPECT_EQ(buffer.sbumpc(), 'B');
    EXPECT_EQ(buffer.sbumpc(), 'C');
    EXPECT_EQ(buffer.sbumpc(), 'D');
}
