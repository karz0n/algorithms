#pragma once

#include "DynamicBitSet.hpp"

#include <map>
#include <vector>
#include <string>
#include <string_view>

namespace algorithms::huffman {

/** One symbol representation */
using Symbol = std::uint8_t;

/** Multiple symbols representation */
using Symbols = std::vector<Symbol>;

/**
 * Huffman node implementation.
 */
struct Node final {
    explicit Node(Symbol symbol, std::size_t weight = 0)
        : symbol{symbol}
        , weight{weight}
    {
    }

    Node(const Node* lhNode, const Node* rhNode)
        : lh{lhNode}
        , rh{rhNode}
    {
        weight = lh->weight + rh->weight;
    }

    ~Node()
    {
        delete lh;
        delete rh;
    }

    [[nodiscard]] bool
    isLeaf() const
    {
        return !(lh || rh);
    }

public:
    Node(const Node&) = delete;

    Node&
    operator=(const Node&)
        = delete;

public:
    Symbol symbol{0};
    std::size_t weight{0};
    const Node* lh{nullptr};
    const Node* rh{nullptr};
};

/**
 * Huffman tree implementation.
 */
class Tree final {
public:
    explicit Tree(const DynamicBitSet& bits);

    explicit Tree(std::string_view input);

    ~Tree();

    [[nodiscard]] const Node*
    root() const;

    [[nodiscard]] bool
    empty() const;

    [[nodiscard]] DynamicBitSet
    serialize() const;

    void
    deserialize(const DynamicBitSet& bits);

public:
    Tree(const Tree&) = delete;

    Tree&
    operator=(const Tree&)
        = delete;

private:
    void
    compose(std::string_view input);

    static void
    putNodes(const Node* node, DynamicBitSet& bits);

    [[nodiscard]] static const Node*
    getNodes(DynamicBitSet& bits);

private:
    const Node* _root{nullptr};
};

/**
 * Huffman encoder implementation.
 */
class Encoder {
public:
    explicit Encoder(const Tree& tree);

    [[nodiscard]] const DynamicBitSet&
    encode(Symbol input) const;

    [[nodiscard]] DynamicBitSet
    encode(std::string_view input) const;

public:
    Encoder(const Encoder&) = delete;

    Encoder&
    operator=(const Encoder&)
        = delete;

private:
    void
    composeMap(const Tree& tree);

    void
    composeEntry(const Node* node, DynamicBitSet value);

private:
    std::map<Symbol, DynamicBitSet> _map;
};

/**
 * Huffman decoder implementation.
 */
class Decoder {
public:
    explicit Decoder(const Tree& tree);

    [[nodiscard]] std::string
    decode(const DynamicBitSet& bitSet) const;

public:
    Decoder(const Decoder&) = delete;

    Decoder&
    operator=(const Decoder&)
        = delete;

private:
    const Node* _root{nullptr};
};

/**
 * Encodes given input.
 * @param input The given sequence of chars to encode.
 * @return The outcome of encoding of given sequence of chars.
 */
[[nodiscard]] extern Symbols
encode(std::string_view input);

/**
 * Decodes given dataset.
 * @param bytes The dataset which represents encoded sequence of chars.
 * @return The sequence of original sequence of chars.
 */
[[nodiscard]] extern std::string
decode(Symbols symbols);

} // namespace algorithms::huffman