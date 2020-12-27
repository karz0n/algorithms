#include "DirectedCycleFinder.hpp"

#include <functional>

namespace algorithms {

using Callback = std::function<bool(const std::size_t)>;

template<typename T>
void
forEachAdjacency(const T&, std::size_t s, const Callback& callback);

template<>
void
forEachAdjacency<Digraph>(const Digraph& graph, std::size_t s, const Callback& callback)
{
    for (const std::size_t w : graph.adjacency(s)) {
        if (!callback(w)) {
            break;
        }
    }
}

template<>
void
forEachAdjacency<EdgeWeightedDigraph>(const EdgeWeightedDigraph& graph,
                                      std::size_t s,
                                      const Callback& callback)
{
    for (const auto& edge : graph.adjacency(s)) {
        const std::size_t w{edge.to()};
        if (!callback(w)) {
            break;
        }
    }
}

DirectedCycleFinder::DirectedCycleFinder(const Digraph& graph)
{
    traverse(graph);
}

DirectedCycleFinder::DirectedCycleFinder(const EdgeWeightedDigraph& graph)
{
    traverse(graph);
}

bool
DirectedCycleFinder::hasCycle() const
{
    return !_cycle.empty();
}

const Vertices&
DirectedCycleFinder::cycle() const
{
    return _cycle;
}

template<typename GraphType>
void
DirectedCycleFinder::traverse(const GraphType& graph)
{
    Marks visitMarks(graph.verticesCount(), false);
    Marks stackMarks(graph.verticesCount(), false);

    for (std::size_t s = 0; s < graph.verticesCount(); ++s) {
        if (!visitMarks[s]) {
            Vertices parentLinks(graph.verticesCount());
            traverse(graph, s, visitMarks, stackMarks, parentLinks);
        }
    }
}

template<typename GraphType>
void
DirectedCycleFinder::traverse(const GraphType& graph,
                              std::size_t s,
                              Marks& visitMarks,
                              Marks& stackMarks,
                              Vertices& parentLinks)
{
    visitMarks[s] = true; // Mark vertex as visited
    stackMarks[s] = true; // Mark vertex as active on stack call

    forEachAdjacency(graph, s, [&](const std::size_t w) {
        if (!visitMarks[w]) {
            parentLinks[w] = s;
            traverse(graph, w, visitMarks, stackMarks, parentLinks);
        }

        if (hasCycle()) {
            // Cycle has already found (stop traverse vertices)
            return false;
        }

        if (stackMarks[w]) {
            // Cycle has just found (make chain of vertices and stop traverse vertices)
            makeCycleChain(parentLinks, s, w);
            return false;
        }

        return true;
    });

    stackMarks[s] = false; // Mark vertex as inactive on stack call
}

void
DirectedCycleFinder::makeCycleChain(const Vertices& parentLinks, std::size_t s, std::size_t w)
{
    _cycle.push_back(w);
    for (std::size_t p = s; p != w; p = parentLinks[p]) {
        _cycle.push_back(p);
    }
    _cycle.push_back(w);
    std::reverse(_cycle.begin(), _cycle.end());
}

} // namespace algorithms