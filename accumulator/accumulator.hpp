
#pragma once

#include <cmath>

class accumulator
{
public:
    accumulator() : count_(0), sum_(0.0), sum_squares_(0.0) {}
    template <typename Arithmetic>
    void accumulate(const Arithmetic& n)
    {
        ++count_;
        sum_ += n;
        sum_squares_ += (n * n);
    }
    template <typename Arithmetic>
    void operator()(const Arithmetic& n)
    {
        accumulate(n);
    }
    size_t count() { return count_; }
    double total() { return sum_; }
    double mean() { return sum_ / count_; }

#if 0
    double stddev()
    {
        return std::sqrt((sum_squares_ - ((sum_ * sum_) / count_)) /
                         (count_ - 1));
    }
#else
    double variance()
    {
        const auto mean = this->mean();
        return (sum_squares_ / count_) - (mean * mean);
    }
    double stddev()
    {
        const auto correction = (double)count_ / (count_ - 1);
        return std::sqrt(variance() * correction);
    }
#endif

private:
    size_t count_;
    double sum_;
    double sum_squares_;
};