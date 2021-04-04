#include "Huffman.hpp"

#include "MemoryStreamBuffer.hpp"

#include <queue>
#include <array>

/** Tree Implementation */
namespace algorithms::huffman {

Tree::Tree(const DynamicBitSet& bits)
{
    deserialize(bits);
}

Tree::Tree(std::string_view input)
{
    compose(input);
}

Tree::~Tree()
{
    delete _root;
}

const Node*
Tree::root() const
{
    return _root;
}

bool
Tree::empty() const
{
    return (_root == nullptr);
}

void
Tree::compose(std::string_view input)
{
    static const std::size_t R = std::numeric_limits<Symbol>::max() + 1;

    std::array<std::size_t, R> frequency = {};
    for (const Symbol ch : input) {
        frequency[ch]++;
    }

    auto cmp = [](const Node* lh, const Node* rh) { return lh->weight > rh->weight; };
    std::priority_queue<const Node*, std::vector<const Node*>, decltype(cmp)> queue(cmp);
    for (std::size_t ch{0}; ch < R; ++ch) {
        if (frequency[ch] > 0) {
            queue.push(new Node(ch, frequency[ch]));
        }
    }

    while (queue.size() > 1) {
        const auto* n1 = queue.top();
        queue.pop();
        const auto* n2 = queue.top();
        queue.pop();
        queue.push(new Node(n1, n2));
    }
    const auto* rootNode = queue.top();
    queue.pop();

    _root = rootNode;
}

DynamicBitSet
Tree::serialize() const
{
    DynamicBitSet output;
    putNodes(_root, output);
    return output;
}

void
Tree::deserialize(const DynamicBitSet& bits)
{
    DynamicBitSet input{bits.reverse()};
    _root = getNodes(input);
}

void
Tree::putNodes(const Node* node, DynamicBitSet& bits)
{
    if (node->isLeaf()) {
        bits.putBit(true);
        bits.putByte(static_cast<std::byte>(node->symbol));
        return;
    }

    bits.putBit(false);
    putNodes(node->lh, bits);
    putNodes(node->rh, bits);
}

const Node*
Tree::getNodes(DynamicBitSet& bits)
{
    if (bits.popBit()) {
        const auto byte{bits.popByte(std::endian::little)};
        return new Node{std::to_integer<std::uint8_t>(byte)};
    }
    auto lh = getNodes(bits);
    auto rh = getNodes(bits);
    return new Node{lh, rh};
}

} // namespace algorithms::huffman

/** Encoder Implementation */
namespace algorithms::huffman {

Encoder::Encoder(const Tree& tree)
{
    composeMap(tree);
}

const DynamicBitSet&
Encoder::encode(Symbol input) const
{
    return _map.at(input);
}

DynamicBitSet
Encoder::encode(std::string_view input) const
{
    DynamicBitSet bitSet;
    for (const auto symbol : input) {
        bitSet += encode(symbol);
    }
    return bitSet;
}

void
Encoder::composeMap(const Tree& tree)
{
    DynamicBitSet value;
    composeEntry(tree.root(), std::move(value));
}

void
Encoder::composeEntry(const Node* node, DynamicBitSet value)
{
    if (node->isLeaf()) {
        _map.emplace(node->symbol, std::move(value));
        return;
    }

    DynamicBitSet lhValue{value};
    lhValue.putBit(false);
    composeEntry(node->lh, std::move(lhValue));

    DynamicBitSet rhValue{std::move(value)};
    rhValue.putBit(true);
    composeEntry(node->rh, std::move(rhValue));
}

} // namespace algorithms::huffman

/** Decoder Implementation */
namespace algorithms::huffman {

Decoder::Decoder(const Tree& tree)
    : _root{tree.root()}
{
}

std::string
Decoder::decode(const DynamicBitSet& bitSet) const
{
    std::string output;
    std::size_t p{0};
    while (p < bitSet.size()) {
        const Node* node{_root};
        while (!node->isLeaf()) {
            if (p == bitSet.size()) {
#ifndef NDEBUG
                throw std::runtime_error{"Invalid data set"};
#else
                return output;
#endif
            }
            node = bitSet[p++] ? node->rh : node->lh;
        }
        output += node->symbol;
    }
    return output;
}

} // namespace algorithms::huffman

/** Encoding And Decoding Implementation */
namespace algorithms::huffman {

struct HuffmanHeader {
    std::uint32_t dataBits{0};
    std::uint32_t treeBits{0};
};

bool
read(MemoryStreamBuffer& buffer, HuffmanHeader& header)
{
    auto b1 = buffer.sbumpc();
    auto b2 = buffer.sbumpc();
    auto b3 = buffer.sbumpc();
    if (b1 != 'H' || b2 != 'U' || b3 != 'F') {
        return false;
    }

    const std::size_t count = sizeof(header);
    if (buffer.sgetn(reinterpret_cast<std::uint8_t*>(&header), count) != count) {
        return false;
    }
    return true;
}

bool
read(MemoryStreamBuffer& buffer, DynamicBitSet& bits, std::size_t count)
{
    return (buffer.get(bits, count) == count);
}

void
write(MemoryStreamBuffer& buffer, const HuffmanHeader& header)
{
    buffer.sputc('H');
    buffer.sputc('U');
    buffer.sputc('F');
    buffer.sputn(reinterpret_cast<const std::uint8_t*>(&header), sizeof(header));
}

void
write(MemoryStreamBuffer& buffer, const DynamicBitSet& bits)
{
    buffer.put(bits);
}

Symbols
encode(std::string_view input)
{
    if (input.empty()) {
        return {};
    }

    const Tree tree{input};
    const auto treeBits = tree.serialize();

    Encoder encoder{tree};
    const auto dataBits = encoder.encode(input);

    HuffmanHeader header;
    header.dataBits = dataBits.size();
    header.treeBits = treeBits.size();

    MemoryStreamBuffer buffer;
    write(buffer, header);
    write(buffer, treeBits);
    write(buffer, dataBits);
    return buffer.extract();
}

std::string
decode(Symbols symbols)
{
    if (symbols.empty()) {
        return {};
    }

    MemoryStreamBuffer buffer{std::move(symbols)};
    HuffmanHeader header;
    if (!read(buffer, header)) {
        return {};
    }

    DynamicBitSet trieBits;
    if (!read(buffer, trieBits, header.treeBits)) {
        return {};
    }
    const Tree tree{trieBits};

    DynamicBitSet dataBits;
    if (!read(buffer, dataBits, header.dataBits)) {
        return {};
    }
    Decoder decoder{tree};
    return decoder.decode(dataBits);
}

} // namespace algorithms::huffman
