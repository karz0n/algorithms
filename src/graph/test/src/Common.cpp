#include "Common.hpp"

#include <fstream>
#include <stdexcept>

using namespace algorithms;

void
readGraph(const fs::path& path, Graph& graph)
{
    std::ifstream s{path};
    if (!s) {
        throw std::runtime_error{"Failed to open file"};
    }

    std::size_t vertices{};
    std::size_t edges{};

    s >> vertices;
    if (!s || !vertices) {
        throw std::runtime_error{"Failed to read number of vertices or it's invalid"};
    }
    s >> edges;
    if (!s || !edges) {
        throw std::runtime_error{"Failed to reader number of edges or it's invalid"};
    }

    graph.reset(vertices);
    std::size_t v{};
    std::size_t w{};
    while (s) {
        s >> v >> w;
        if (!s) {
            break;
        }
        if (v > vertices || w > vertices) {
            throw std::runtime_error{"Invalid number of vertex"};
        }
        graph.connect(v, w);
    }
}

void
readGraph(const fs::path& path, algorithms::EdgeWeightedGraph& graph)
{
    std::ifstream s{path};
    if (!s) {
        throw std::runtime_error{"Failed to open file"};
    }

    std::size_t vertices{};
    std::size_t edges{};

    s >> vertices;
    if (!s || !vertices) {
        throw std::runtime_error{"Failed to read number of vertices or it's invalid"};
    }
    s >> edges;
    if (!s || !edges) {
        throw std::runtime_error{"Failed to reader number of edges or it's invalid"};
    }

    graph.reset(vertices);
    std::size_t v{};
    std::size_t w{};
    double weight{};
    while (s) {
        s >> v >> w >> weight;
        if (!s) {
            break;
        }
        if (v > vertices || w > vertices) {
            throw std::runtime_error{"Invalid number of vertex"};
        }
        graph.add(Edge{v, w, weight});
    }
}
