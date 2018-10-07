#include <iostream>
#include <random>
#include <numeric>

#include "Percolation.hpp"

using namespace algorithms::uf;

/**
 * The number of samples to get of percolation threshold.
 */
const std::size_t NUMBER_OF_SAMPLES = 100;

/**
 * The width of experimental model.
 */
const std::size_t WIDTH_OF_MODEL = 100;

/**
 * Simulate on model with given width and randomly opened sites.
 *
 * The percolation threshold indicates amount of percents of opened sites
 * in percolation model which percolated with high probability.
 *
 * @param width The width of model.
 *
 * @return The percolation threshold.
 */
double simulate(std::size_t width)
{
    Percolation percolation(width);

    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<std::size_t> dist(0, percolation.totalCount() - 1);

    bool p = false;
    while (!p) {
        std::size_t site = dist(engine);
        if (!percolation.isOpened(site)) {
            percolation.open(site);
        }
        p = percolation.isPercolated();
    }

    std::size_t opened = percolation.countOfOpened();
    double threshold = double(opened) / percolation.totalCount();
    return threshold;
}

int main()
{
    std::vector<double> values(NUMBER_OF_SAMPLES);
    for (std::size_t i = 0; i < NUMBER_OF_SAMPLES; ++i) {
        values[i] = simulate(WIDTH_OF_MODEL);
    }

    double sum = std::accumulate(values.cbegin(), values.cend(), 0.0);
    double mean = sum / values.size();

    std::cout << "The percolation threshold: " << mean << std::endl;
}
