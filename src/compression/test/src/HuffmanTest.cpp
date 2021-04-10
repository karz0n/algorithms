#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Huffman.hpp"

using namespace testing;
using namespace algorithms;

TEST(HuffmanTest, TreeSerialize)
{
    static const std::string_view text{"AABBCDEF"};

    const huffman::Tree tree{text};
    EXPECT_FALSE(tree.empty());

    auto bitSet = tree.serialize().reverse();
    EXPECT_THAT(bitSet, Not(IsEmpty()));
    EXPECT_THAT(bitSet, SizeIs(Gt(0)));

    EXPECT_FALSE(bitSet.popBit());
    EXPECT_FALSE(bitSet.popBit());
    EXPECT_TRUE(bitSet.popBit());
    EXPECT_EQ(bitSet.popByte(std::endian::little), std::byte{0b01000001} /* A */);
    EXPECT_FALSE(bitSet.popBit());
    EXPECT_TRUE(bitSet.popBit());
    EXPECT_EQ(bitSet.popByte(std::endian::little), std::byte{0b01000011} /* C */);
    EXPECT_TRUE(bitSet.popBit());
    EXPECT_EQ(bitSet.popByte(std::endian::little), std::byte{0b01000110} /* F */);
    EXPECT_FALSE(bitSet.popBit());
    EXPECT_TRUE(bitSet.popBit());
    EXPECT_EQ(bitSet.popByte(std::endian::little), std::byte{0b01000010} /* B */);
    EXPECT_FALSE(bitSet.popBit());
    EXPECT_TRUE(bitSet.popBit());
    EXPECT_EQ(bitSet.popByte(std::endian::little), std::byte{0b01000100} /* D */);
    EXPECT_TRUE(bitSet.popBit());
    EXPECT_EQ(bitSet.popByte(std::endian::little), std::byte{0b01000101} /* E */);

    EXPECT_THAT(bitSet, IsEmpty());
    EXPECT_THAT(bitSet, SizeIs(0));
}

TEST(HuffmanTest, TreeDeserialize)
{
    DynamicBitSet bitSet;
    bitSet.putBits({false, false, true});
    bitSet.putByte(std::byte{'A'});
    bitSet.putBits({false, true});
    bitSet.putByte(std::byte{'C'});
    bitSet.putBits({true});
    bitSet.putByte(std::byte{'F'});
    bitSet.putBits({false, true});
    bitSet.putByte(std::byte{'B'});
    bitSet.putBits({false, true});
    bitSet.putByte(std::byte{'D'});
    bitSet.putBits({true});
    bitSet.putByte(std::byte{'E'});

    const huffman::Tree tree{bitSet};
    EXPECT_FALSE(tree.empty());

    huffman::Encoder encoder{tree};
    EXPECT_EQ(encoder.encode('A'), DynamicBitSet({false, false}));
    EXPECT_EQ(encoder.encode('B'), DynamicBitSet({true, false}));
    EXPECT_EQ(encoder.encode('C'), DynamicBitSet({false, true, false}));
    EXPECT_EQ(encoder.encode('D'), DynamicBitSet({true, true, false}));
    EXPECT_EQ(encoder.encode('E'), DynamicBitSet({true, true, true}));
    EXPECT_EQ(encoder.encode('F'), DynamicBitSet({false, true, true}));
}

TEST(HuffmanTest, Encode)
{
    static const std::string_view input{"AABAB"};

    const huffman::Tree tree{input};
    EXPECT_FALSE(tree.empty());

    huffman::Encoder encoder{tree};
    EXPECT_EQ(encoder.encode(input), DynamicBitSet({true, true, false, true, false}));
}

TEST(HuffmanTest, Decode)
{
    static const std::string_view input{"AABAB"};

    const huffman::Tree tree{input};
    EXPECT_FALSE(tree.empty());

    huffman::Decoder decoder{tree};
    EXPECT_EQ(decoder.decode({true, true, false, true, false}), input);
}

TEST(HuffmanTest, Reconstruction)
{
    static const std::string_view text{"Peter Piper picked a peck of pickled peppers\n"
                                       "A peck of pickled peppers Peter Piper picked\n"
                                       "If Peter Piper picked a peck of pickled peppers\n"
                                       "Where's the peck of pickled peppers Peter Piper picked?"};

    const auto data = huffman::encode(text);
    EXPECT_EQ(huffman::decode(data), text);
}