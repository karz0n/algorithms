#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "DynamicBitSet.hpp"

using namespace testing;
using namespace algorithms;

TEST(DynamicBitSetTest, PutPopBit)
{
    DynamicBitSet bitSet;
    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));

    bitSet.putBit(false);
    bitSet.putBit(true);
    bitSet.putBit(true);

    EXPECT_THAT(bitSet, Not(IsEmpty()));
    EXPECT_THAT(bitSet, SizeIs(Gt(0)));

    EXPECT_THAT(bitSet.popBit(), IsTrue());
    EXPECT_THAT(bitSet.popBit(), IsTrue());
    EXPECT_THAT(bitSet.popBit(), IsFalse());

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));
}

TEST(DynamicBitSetTest, PutPopByte)
{
    DynamicBitSet bitSet;

    const std::byte value{0b01010011};

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));

    bitSet.putByte(value);

    EXPECT_THAT(bitSet, Not(IsEmpty()));
    EXPECT_THAT(bitSet, SizeIs(DynamicBitSet::BitsInByte));

    EXPECT_EQ(bitSet.popByte(), value);

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));
}

TEST(DynamicBitSetTest, PutBits)
{
    DynamicBitSet bitSet;

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));

    std::uint64_t value{42};
    bitSet.putBits(value, DynamicBitSet::BitsInByte);
    EXPECT_EQ(bitSet.popBits(DynamicBitSet::BitsInByte), value);

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));

    bitSet.putBits({true, false, true});

    EXPECT_THAT(bitSet.popBit(), IsTrue());
    EXPECT_THAT(bitSet.popBit(), IsFalse());
    EXPECT_THAT(bitSet.popBit(), IsTrue());

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));
}

TEST(DynamicBitSetTest, PutBytes)
{
    DynamicBitSet bitSet;

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));

    const std::byte b1{0b01010011};
    const std::byte b2{0b00001111};

    bitSet.putBytes({b1, b2});

    EXPECT_EQ(bitSet.popByte(), b2);
    EXPECT_EQ(bitSet.popByte(), b1);

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));
}

TEST(DynamicBitSetTest, Reverse)
{
    DynamicBitSet bitSet;
    bitSet.putByte(std::byte{0b11110000});
    auto reverse = bitSet.reverse();
    EXPECT_EQ(reverse.popByte(), std::byte{0b00001111});
}

TEST(DynamicBitSetTest, EqualAndNot)
{
    DynamicBitSet bitSet1;
    bitSet1.putByte(std::byte{0b00001111});
    DynamicBitSet bitSet2;
    bitSet2.putByte(std::byte{0b11110000});
    DynamicBitSet bitSet3;
    bitSet3.putByte(std::byte{0b00001111});

    EXPECT_EQ(bitSet1, bitSet3);
    EXPECT_NE(bitSet1, bitSet2);
}
