#pragma once

#include "Router.hpp"

namespace algorithms {

class DepthFirstRoutes final : public Router {
public:
    void
    calculate(const Graph& graph, std::size_t s) override;

private:
    void
    traverse(const Graph& graph, std::size_t s);
};

} // namespace algorithms
