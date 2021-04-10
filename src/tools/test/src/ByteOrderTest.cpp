#include <gtest/gtest.h>

#include "ByteOrder.hpp"

using namespace testing;
using namespace algorithms;

TEST(ByteOrderTest, NotEqEndian)
{
    EXPECT_EQ(ByteOrder::convert<std::uint16_t>(0xFF00, std::endian::big, std::endian::little),
              0x00FF);
    EXPECT_EQ(ByteOrder::convert<std::uint16_t>(0xFF00, std::endian::little, std::endian::big),
              0x00FF);

    EXPECT_EQ(ByteOrder::convert<std::uint32_t>(0xFF00FF00, std::endian::big, std::endian::little),
              0x00FF00FF);
    EXPECT_EQ(ByteOrder::convert<std::uint32_t>(0xFF00FF00, std::endian::little, std::endian::big),
              0x00FF00FF);

    EXPECT_EQ(ByteOrder::convert<std::uint64_t>(
                  0xFF00FF00FF00FF00, std::endian::big, std::endian::little),
              0x00FF00FF00FF00FF);
    EXPECT_EQ(ByteOrder::convert<std::uint64_t>(
                  0xFF00FF00FF00FF00, std::endian::little, std::endian::big),
              0x00FF00FF00FF00FF);
}

TEST(ByteOrderTest, EqEndian)
{
    EXPECT_EQ(ByteOrder::convert<std::uint16_t>(0xFF00, std::endian::big, std::endian::big),
              0xFF00);
    EXPECT_EQ(ByteOrder::convert<std::uint32_t>(0xFF00FF00, std::endian::big, std::endian::big),
              0xFF00FF00);
    EXPECT_EQ(
        ByteOrder::convert<std::uint64_t>(0xFF00FF00FF00FF00, std::endian::big, std::endian::big),
        0xFF00FF00FF00FF00);

    EXPECT_EQ(ByteOrder::convert<std::uint16_t>(0xFF00, std::endian::little, std::endian::little),
              0xFF00);
    EXPECT_EQ(
        ByteOrder::convert<std::uint32_t>(0xFF00FF00, std::endian::little, std::endian::little),
        0xFF00FF00);
    EXPECT_EQ(ByteOrder::convert<std::uint64_t>(
                  0xFF00FF00FF00FF00, std::endian::little, std::endian::little),
              0xFF00FF00FF00FF00);

    EXPECT_EQ(ByteOrder::convert<std::uint16_t>(0xFF00, std::endian::native, std::endian::native),
              0xFF00);
    EXPECT_EQ(
        ByteOrder::convert<std::uint32_t>(0xFF00FF00, std::endian::native, std::endian::native),
        0xFF00FF00);
    EXPECT_EQ(ByteOrder::convert<std::uint64_t>(
                  0xFF00FF00FF00FF00, std::endian::native, std::endian::native),
              0xFF00FF00FF00FF00);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
TEST(ByteOrderTest, Native)
{
    if (std::endian::native == std::endian::big) {
        EXPECT_EQ(
            ByteOrder::convert<std::uint16_t>(0xFF00, std::endian::native, std::endian::little),
            0x00FF);
        EXPECT_EQ(
            ByteOrder::convert<std::uint32_t>(0xFF00FF00, std::endian::native, std::endian::little),
            0x00FF00FF);
        EXPECT_EQ(ByteOrder::convert<std::uint64_t>(
                      0xFF00FF00FF00FF00, std::endian::native, std::endian::little),
                  0x00FF00FF00FF00FF);
    }

    if (std::endian::native == std::endian::little) {
        EXPECT_EQ(ByteOrder::convert<std::uint16_t>(0xFF00, std::endian::big, std::endian::native),
                  0x00FF);
        EXPECT_EQ(
            ByteOrder::convert<std::uint32_t>(0xFF00FF00, std::endian::big, std::endian::native),
            0x00FF00FF);
        EXPECT_EQ(ByteOrder::convert<std::uint64_t>(
                      0xFF00FF00FF00FF00, std::endian::big, std::endian::native),
                  0x00FF00FF00FF00FF);
    }
}
#pragma clang diagnostic pop