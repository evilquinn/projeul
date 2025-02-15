
#pragma once

#include <cmath>

class accumulator
{
public:
    accumulator() : count_(0), sum_(0.0), sum_squares_(0.0), is_population_(false) {}
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

#if 1
    double stddev()
    {
        auto divisor = count_;
        if (!is_population_)
        {
            divisor = count_ - 1;
        }
        return std::sqrt((sum_squares_ - ((sum_ * sum_) / count_)) / divisor);
    }
#else
    double variance()
    {
        const auto mean = this->mean();
        return (sum_squares_ / count_) - (mean * mean);
    }
    double stddev()
    {
        double correction = 1;
        if (!is_population_)
        {
            correction = (double)count_ / (count_ - 1);
        }
        return std::sqrt(variance() * correction);
    }
#endif
    void set_population(bool is_population) { is_population_ = is_population; }

private:
    size_t count_;
    double sum_;
    double sum_squares_;
    bool is_population_;
};