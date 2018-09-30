
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
    a(ina), b(inb), c(calc_c()), sadj(a<=b?a:b), ladj(a>b?a:b)
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
    return sadj == rhs.sadj ? ladj < rhs.ladj
                            : sadj < rhs.sadj;
}

bool triplet::equal(const triplet& rhs) const
{
    return sadj == rhs.sadj && ladj == rhs.ladj;
}

triplets_t gen_triplets(size_t alimit)
{
    triplets_t result;
    for ( size_t p = 2; p < alimit/2; ++p )
    {
        for ( size_t q = 1; q < p; ++q )
        {
            if ( ( ( p & 0x1 ) != 0u ) && ( ( q & 0x1 ) != 0u ) )
            {
                continue;
            }

            size_t a = 2 * p * q;
            if ( a > alimit )
            {
                break;
            }
            size_t b = p * p - q * q;
            size_t c = p * p + q * q;
            triplet cand(a, b, c);
            result.insert(cand);
        }
    }
    return result;
}
} // end namespace pyth
