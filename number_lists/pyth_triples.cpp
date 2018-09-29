
#include <pyth_triples.hpp>
#include <cmath>
#include <sstream>

namespace pyth {

size_t triplet::calc_c()
{
    size_t sum = a*a + b*b;
    size_t result = std::sqrt(sum);
    if ( result * result != sum )
    {
        std::stringstream error;
        error << "invalid pythagorean triplet: a=" << a << ", b=" << b;
        throw invalid_argument(error.str());
    }
    return result;
}
triplet::triplet(const size_t ina, const size_t inb) :
    a(ina), b(inb), c(calc_c()), sadj(a<=b?&a:&b), ladj(a>b?&a:&b)
{
}
triplet::triplet(const size_t ina, const size_t inb, const size_t inc) :
    triplet(ina, inb)
{
    if ( c != inc )
    {
        std::stringstream error;
        error << "c=" << inc << " is invalid:"
              << " a=" << a << " and b=" << b << " means c=" << c;
        throw invalid_argument(error.str());
    }
}

bool triplet::less_than(const triplet& rhs) const
{
    return *sadj == *rhs.sadj ? *ladj < *rhs.ladj
                              : *sadj < *rhs.sadj;
}

} // end namespace pyth
