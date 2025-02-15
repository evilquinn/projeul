

#include <vector>

#include <gmock/gmock.h>

#include "accumulator.hpp"

TEST(AccumulatorTest, CountIsCorrect)
{
    std::vector<std::vector<int>> samples = { { 128, 219, 316, 189, 512, 98, 155, 110, 468, 177, 203, 73, 252 } };

    for (auto&& sample : samples)
    {
        accumulator accer;
        for (auto&& value : sample)
        {
            accer(value);
        }
        EXPECT_THAT(accer.count(), testing::Eq(sample.size()));
    }
}

TEST(AccumulatorTest, MeanIsCorrect)
{
    std::vector<std::pair<std::vector<int>, std::pair<double, double>>> samples = {
        { { 128, 219, 316, 189, 512, 98, 155, 110, 468, 177, 203, 73, 252 }, { 223.0769, 0.00005 } }
    };

    for (auto&& sample : samples)
    {
        accumulator accer;
        for (auto&& value : sample.first)
        {
            accer(value);
        }
        EXPECT_THAT(accer.mean(), testing::DoubleNear(sample.second.first, sample.second.second));
    }
}

TEST(AccumulatorTest, PopulationStandardDeviationIsCorrect)
{
    // list of tests, each test includes list of values, and a pair representing the expected outcome and how accurate
    // we expect it to be
    std::vector<std::pair<std::vector<int>, std::pair<double, double>>> samples = {
        { { 128, 219, 316, 189, 512, 98, 155, 110, 468, 177, 203, 73, 252 }, { 130.4628, 0.00005 } },
        { { 6, 2, 3, 1 }, { 1.87, 0.005 } },
        { { 10, 2 }, { 4.0, 0.05 } },
        { { 10, 12, 15, 18, 20 }, { 3.69, 0.005 } },
        { { 4, 9, 11, 12, 17, 5, 8, 12, 14 }, { 3.94, 0.005 } },
        { { 9, 2, 5, 4, 12, 7, 8, 11, 9, 3, 7, 4, 12, 5, 4, 10, 9, 6, 9, 4 }, { 2.983, 0.0005 } }
    };

    for (auto&& sample : samples)
    {
        accumulator accer;
        accer.set_population(true);
        for (auto&& value : sample.first)
        {
            accer(value);
        }
        EXPECT_THAT(accer.stddev(), testing::DoubleNear(sample.second.first, sample.second.second));
    }
}

TEST(AccumulatorTest, SampleStandardDeviationIsCorrect)
{
    std::vector<std::pair<std::vector<int>, std::pair<double, double>>> samples = {
        { { 128, 219, 316, 189, 512, 98, 155, 110, 468, 177, 203, 73, 252 }, { 135.7899, 0.00005 } },
        { { 6, 2, 3, 1 }, { 2.16, 0.005 } },
        { { 10, 2 }, { 5.66, 0.005 } },
        { { 2, 2, 5, 7 }, { 2.45, 0.005 } },
        { { 2, 4, 4, 6, 8 }, { 2.28, 0.005 } },
        { { 10, 12, 15, 18, 20 }, { 4.12, 0.005 } },
        { { 9, 6, 8, 5, 7 }, { 1.58, 0.005 } },
        { { 51, 38, 79, 46, 57 }, { 15.51, 0.005 } },
        { { 4, 7, 9, 10, 16 }, { 4.4, 0.05 } },
        { { 9, 2, 5, 4, 12, 7 }, { 3.619, 0.0005 } }
    };

    for (auto&& sample : samples)
    {
        accumulator accer;
        for (auto&& value : sample.first)
        {
            accer(value);
        }
        EXPECT_THAT(accer.stddev(), testing::DoubleNear(sample.second.first, sample.second.second));
    }
}
