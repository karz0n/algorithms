#include <BreadthFirstSearchRouter.hpp>

#include <queue>

namespace algorithms {

void
BreadthFirstSearchRoutes::calculate(const Graph& graph, std::size_t s)
{
    init(graph, s);
    traverse(graph, s);
}

void
BreadthFirstSearchRoutes::traverse(const Graph& graph, std::size_t s)
{
    std::queue<std::size_t> vs;
    vs.push(s);
    marked[s] = true;
    while (!vs.empty()) {
        s = vs.front();
        vs.pop();
        for (std::size_t w : graph.adjacency(s)) {
            if (!marked[w]) {
                vs.push(w);
                edgeTo[w] = s;
                marked[w] = true;
            }
        }
    }
}

} // namespace algorithms
