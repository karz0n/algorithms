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

    std::size_t vertices{0};
    std::size_t edges{0};

    s >> vertices;
    if (!s || !vertices) {
        throw std::runtime_error{"Failed to read number of vertices or it's invalid"};
    }
    s >> edges;
    if (!s || !edges) {
        throw std::runtime_error{"Failed to reader number of edges or it's invalid"};
    }

    graph.reset(vertices);
    std::size_t v1{0};
    std::size_t v2{0};
    while (s) {
        s >> v1 >> v2;
        if (!s) {
            break;
        }
        if (v1 > vertices || v2 > vertices) {
            throw std::runtime_error{"Invalid number of vertex"};
        }
        graph.connect(v1, v2);
    }
}
