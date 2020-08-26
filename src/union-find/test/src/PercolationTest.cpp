#include <iostream>
#include <numeric>
#include <random>

#include <gtest/gtest.h>

#include "Percolation.hpp"

using namespace algorithms;

/**
 * The number of samples to get of percolation threshold.
 */
const std::size_t NumberOfSamples = 100;

/**
 * Simulate on model with given width and randomly opened sites.
 *
 * Used monte carlo method to open sites in percolation model.
 *
 * The percolation threshold indicates amount of percents of opened sites
 * in percolation model. It shows probability that percolation model
 * is percolated from top to bottom.
 *
 * @param width The width of model.
 *
 * @return The percolation threshold.
 */
double
simulate(Percolation& model)
{
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<std::size_t> dist(0, model.totalCount() - 1);

    bool percolated = false;
    while (!percolated) {
        std::size_t site = dist(engine);
        if (!model.isOpened(site)) {
            model.open(site);
            percolated = model.isPercolated();
        }
    }

    std::size_t opened = model.countOfOpened();
    double threshold = double(opened) / model.totalCount();
    return threshold;
}

/**
 * Calculate percolation threshold by calculating mean value between
 * some amount of samples.
 *
 * @param width The width of model.
 *
 * @return The percolation threshold.
 */
double
calculate(Percolation& model)
{
    std::vector<double> values(NumberOfSamples);
    for (std::size_t i = 0; i < NumberOfSamples; ++i) {
        values[i] = simulate(model);
    }
    double sum = std::accumulate(values.cbegin(), values.cend(), 0.0);
    return sum / values.size();
}

TEST(Percolation, w100)
{
    Percolation model(100);
    std::cout << "The percolation threshold: " << calculate(model) << std::endl;
    ASSERT_TRUE(model.isPercolated());
}

TEST(Percolation, w500)
{
    Percolation model(500);
    std::cout << "The percolation threshold: " << calculate(model) << std::endl;
    ASSERT_TRUE(model.isPercolated());
}

TEST(Percolation, w1000)
{
    Percolation model(1000);
    std::cout << "The percolation threshold: " << calculate(model) << std::endl;
    ASSERT_TRUE(model.isPercolated());
}
