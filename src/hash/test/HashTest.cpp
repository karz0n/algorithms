#include <gtest/gtest.h>

#include <Hash.hpp>

#include <functional>

static algorithms::hash<std::string> stringHasher;
static algorithms::hash<double> doubleHasher;

TEST(HashTest, String)
{
    std::string v1{"Hello world!"};
    std::string v2{"Hello World!"};

    auto h1 = stringHasher("Aa");
    auto h2 = stringHasher("BB");

    EXPECT_EQ(stringHasher(v1), stringHasher(v1));
    EXPECT_NE(stringHasher(v1), stringHasher(v2));
}

TEST(HashTest, Double)
{
    double v1{0.01};
    double v2{0.02};

    EXPECT_EQ(doubleHasher(v1), doubleHasher(v1));
    EXPECT_NE(doubleHasher(v1), doubleHasher(v2));
}

TEST(HashTest, Combine)
{
    using namespace algorithms;

    std::string v1{"Hello world!"};
    double v2{0.01};
    int v3{10};

    EXPECT_EQ(combine(v1, v2), combine(v1, v2));
    EXPECT_NE(combine(v1, v2), combine(v1, v3));
}

TEST(HashTest, Collision)
{
    std::hash<std::string> trueStringHasher;

    //! We have a collision with our simple hash method, it's very bad.
    EXPECT_EQ(stringHasher("Aa"), stringHasher("BB"));
    EXPECT_EQ(stringHasher("AaAaAaAa"), stringHasher("BBBBBBBB"));

    //! We don't have a collision with STL hash method, so use it.
    EXPECT_NE(trueStringHasher("Aa"), trueStringHasher("BB"));
    EXPECT_NE(trueStringHasher("AaAaAaAa"), trueStringHasher("BBBBBBBB"));
}
