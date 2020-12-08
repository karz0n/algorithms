#include "Common.hpp"
#include "UnionFind.hpp"

#include <fstream>
#include <stdexcept>
#include <functional>

using namespace algorithms;

namespace fs = std::filesystem;

namespace {

using HeadCallback = std::function<void(std::size_t vertices, std::size_t edges)>;
using LineCallback = std::function<void(const std::string& line)>;

void read(const fs::path& path, const HeadCallback& headCallback, const LineCallback& lineCallback)
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

}

void
readGraph(const fs::path& path, Graph& graph)
{
    const auto headCallback = [&](std::size_t vertices, std::size_t){
        graph.reset(vertices);
    };

    const auto lineCallback = [&](const std::string& line){
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
readGraph(const fs::path& path, EdgeWeightedGraph& graph)
{
    const auto headCallback = [&](std::size_t vertices, std::size_t){
        graph.reset(vertices);
    };

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
readGraph(const fs::path& path, EdgeWeightedDigraph& graph)
{
    const auto headCallback = [&](std::size_t vertices, std::size_t){
        graph.reset(vertices);
    };

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

EdgeWeightedDigraph
readEdgeWeightedDigraph(const std::filesystem::path& path)
{
    EdgeWeightedDigraph graph;
    readGraph(path, graph);
    return graph;
}

void
verifyMinSpanningTree(const Edges& tree, const EdgeWeightedGraph& graph)
{
    /** Checks if min spanning tree contains cycles */
    UnionFind unions{graph.verticesCount()};
    for (const auto& edge : tree) {
        std::size_t v = edge.either();
        std::size_t w = edge.other(v);
        if (unions.find(v) == unions.find(w)) {
            throw std::logic_error{"Not a forest due to cycle detected"};
        }
        unions.associate(v, w);
    }

    /** Checks if the spanning tree doesn't connect all vertices */
    const auto graphEdges = graph.edges();
    for (const auto& edge : graphEdges) {
        std::size_t v = edge.either();
        std::size_t w = edge.other(v);
        if (unions.find(v) != unions.find(w)) {
            throw std::logic_error{"Not a spanning tree"};
        }
    }

    /** Checks that it's a minimal spanning forest (cut optimality conditions) */
    for (const auto edgeS : tree) {
        unions.reset(graph.verticesCount());
        for (const auto edge : tree) {
            if (edge != edgeS) {
                std::size_t v = edge.either();
                std::size_t w = edge.other(v);
                unions.associate(v, w);
            }
        }

        for (const auto edgeG : graphEdges) {
            std::size_t v = edgeG.either();
            std::size_t w = edgeG.other(v);
            if (unions.find(v) != unions.find(w)) {
                if (edgeS.weight() > edgeG.weight()) {
                    throw std::logic_error{"Edge " + edgeG.toString()
                                           + " violates cut optimality conditions"};
                }
            }
        }
    }
}
