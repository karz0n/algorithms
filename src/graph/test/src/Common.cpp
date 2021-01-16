#include "Common.hpp"

#include <stdexcept>
#include <fstream>
#include <functional>

using namespace algorithms;

namespace fs = std::filesystem;

namespace {

using HeadCallback = std::function<void(std::size_t vertices, std::size_t edges)>;
using LineCallback = std::function<void(const std::string& line)>;

void
read(const fs::path& path, const HeadCallback& headCallback, const LineCallback& lineCallback)
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

    headCallback(vertices, edges);

    for (std::string line; std::getline(s, line);) {
        if (line.empty()) {
            continue;
        }
        lineCallback(line);
    }
}

} // namespace

void
read(const fs::path& path, Graph& graph)
{
    const auto headCallback = [&](std::size_t vertices, std::size_t) { graph.reset(vertices); };

    const auto lineCallback = [&](const std::string& line) {
        std::stringstream s{line};
        std::size_t v{};
        std::size_t w{};
        s >> v >> w;
        if (!s) {
            throw std::logic_error{"End of stream"};
        }
        if (v >= graph.verticesCount() || w >= graph.verticesCount()) {
            throw std::runtime_error{"Invalid number of vertex"};
        }
        graph.connect(v, w);
    };

    read(path, headCallback, lineCallback);
}

void
read(const fs::path& path, EdgeWeightedGraph& graph)
{
    const auto headCallback = [&](std::size_t vertices, std::size_t) { graph.reset(vertices); };

    const auto lineCallback = [&](const std::string& line) {
        std::stringstream s{line};
        std::size_t v{};
        std::size_t w{};
        double weight{};
        s >> v >> w >> weight;
        if (!s) {
            throw std::logic_error{"End of stream"};
        }
        if (v >= graph.verticesCount() || w >= graph.verticesCount()) {
            throw std::runtime_error{"Invalid number of vertex"};
        }
        graph.add(Edge{v, w, weight});
    };

    read(path, headCallback, lineCallback);
}

void
read(const fs::path& path, EdgeWeightedDigraph& graph)
{
    const auto headCallback = [&](std::size_t vertices, std::size_t) { graph.reset(vertices); };

    const auto lineCallback = [&](const std::string& line) {
        std::stringstream s{line};
        std::size_t v{};
        std::size_t w{};
        double weight{};
        s >> v >> w >> weight;
        if (!s) {
            throw std::logic_error{"End of stream"};
        }
        if (v >= graph.verticesCount() || w >= graph.verticesCount()) {
            throw std::runtime_error{"Invalid number of vertex"};
        }
        graph.add(DirectedEdge{v, w, weight});
    };

    read(path, headCallback, lineCallback);
}

void
read(const fs::path& path, algorithms::FlowNetwork& network)
{
    const auto headCallback = [&](std::size_t vertices, std::size_t) { network.reset(vertices); };

    const auto lineCallback = [&](const std::string& line) {
        std::stringstream s{line};
        std::size_t v{};
        std::size_t w{};
        double weight{};

        s >> v >> w >> weight;
        if (!s) {
            throw std::logic_error{"End of stream"};
        }
        if (v >= network.verticesCount() || w >= network.verticesCount()) {
            throw std::runtime_error{"Invalid number of vertex"};
        }

        network.add(FlowEdge{v, w, weight});
    };

    read(path, headCallback, lineCallback);
}