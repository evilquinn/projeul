
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <limits>

/*
 * accumulate some stats over a sequence of values
 *
 * accumulates moments of the sequence:
 * zeroith moment is the count of items
 * first moment is the sum of values
 * second moment is the sum of the squares
 */
class super_acca
{
public:
    super_acca() :
        moms_( { 0.0 } ),
        max_(0.0),
        min_(std::numeric_limits<double>::max())
    {}

    void acc(double value)
    {
        if ( value < min_ )
        {
            min_ = value;
        }
        if ( value > max_ )
        {
            max_ = value;
        }
        double increment_by = 1.0;
        for(auto&& mom : moms_)
        {
            mom += increment_by;
            increment_by *= value;
        }
    }
    void acc(const super_acca& other)
    {
        if ( other.min_ < min_ )
        {
            min_ = other.min_;
        }
        if ( other.max_ > max_ )
        {
            max_ = other.max_;
        }
        for(size_t i = 0; i < moms_.size(); ++i)
        {
            moms_[i] += other.moms_[i];
        }
    }
    double stddev() const
    {
        const double mean = moms_[1] / moms_[0];
        const double meanSquare = moms_[2] / moms_[0];
        return std::sqrt(meanSquare - mean * mean);
    }
    double max() const { return max_; }
    double min() const { return min_; }

    std::ostream& to_ostream(std::ostream& os) const
    {
        os << "moments:";
        for(size_t i = 0; i < moms_.size(); ++i)
        {
            os << "\n" << i << ": " << moms_[i];
        }
        os << "\nmax: " << max_
           << "\nmin: " << min_;
        return os;
    }
private:
    std::array<double, 3> moms_;
    double max_;
    double min_;
};

std::ostream& operator<<(std::ostream& os, const super_acca& acca)
{
    return acca.to_ostream(os);
}

int main()
{
    super_acca acca;
    std::vector<double> vals = { 4, 9, 11, 12, 17, 5, 8, 12, 14 };
    for ( auto&& val : vals )
    {
        acca.acc(val);
    }
    std::cout << "acca"
              << " stddev: " << acca.stddev()
              << " max: " << acca.max()
              << " min: " << acca.min() << std::endl;
    super_acca acca2;
    std::vector<double> vals2 = { 1.20, 1.30, 1.24, 1.23, 1.24, 1.28, 1.25 };
    for ( auto&& val : vals2 )
    {
        acca2.acc(val);
    }
    std::cout << "acca2"
              << " stddev: " << acca2.stddev()
              << " max: " << acca2.max()
              << " min: " << acca2.min() << std::endl;
    acca.acc(acca2);
    std::cout << "acca"
              << " stddev: " << acca.stddev()
              << " max: " << acca.max()
              << " min: " << acca.min() << std::endl;
    super_acca acca3;
    std::vector<double> vals3 = { 1.20, 1.30, 1.24, 1.23, 1.24, 1.28, 1.25,
                                  4, 9, 11, 12, 17, 5, 8, 12, 14 };
    for ( auto&& val : vals3 )
    {
        acca3.acc(val);
    }
    std::cout << "acca3"
              << " stddev: " << acca3.stddev()
              << " max: " << acca3.max()
              << " min: " << acca3.min() << std::endl;
    return 0;
}
