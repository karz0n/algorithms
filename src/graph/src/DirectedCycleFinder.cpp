#include "DirectedCycleFinder.hpp"

namespace algorithms {

DirectedCycleFinder::DirectedCycleFinder(const Digraph& graph)
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

void
DirectedCycleFinder::traverse(const Digraph& graph)
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

void
DirectedCycleFinder::traverse(const Digraph& graph,
                              std::size_t s,
                              Marks& visitMarks,
                              Marks& stackMarks,
                              Vertices& parentLinks)
{
    visitMarks[s] = true; // Mark vertex as visited
    stackMarks[s] = true; // Mark vertex as active on stack call

    for (std::size_t v : graph.adjacency(s)) {
        if (!visitMarks[v]) {
            parentLinks[v] = s;
            traverse(graph, v, visitMarks, stackMarks, parentLinks);
        }

        if (hasCycle()) {
            // Cycle has already found (return)
            return;
        }

        if (stackMarks[v]) {
            // Cycle has just found (create chain of vertices and return)
            for (std::size_t w = s; w != v; w = parentLinks[w]) {
                _cycle.push_back(w);
            }
            _cycle.push_back(v);
            _cycle.push_back(s);
            std::reverse(_cycle.begin(), _cycle.end());
            return;
        }
    }

    stackMarks[s] = false; // Mark vertex as inactive on stack call
}

} // namespace algorithms