/*
 * pe77.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <iostream>
#include <map>
#include <pe77.hpp>
#include <utils.hpp>
#include <prime_sieve.hpp>

std::string& pe77::name() { return name_; }

namespace {

size_t prime_limit = 1000;
static prime_sieve primes(prime_limit);

long a(long n)
{
    return primes.is_prime(n) ? 1 : 0;
}

long sopf(long n)
{
    static std::map<long, long> cache;
    if ( cache[n] > 0 )
    {
        return cache[n];
    }

    long result = 0;
    for ( long d = 1; d <= n; ++d )
    {
        if ( n % d == 0 )
        {
            result += d * a(d);
        }
    }

    cache[n] = result;
    return result;
}

long b(long n)
{
    static std::map<long, long> cache = { { 0, 1 },
                                          { 1, sopf(1) } };
    if ( cache[n] > 0 || n < 2 )
    {
        return cache[n];
    }

    long result = 0;
    for ( long k = 1; k <= n; ++k )
    {
        long sopfk = sopf(k);
        long right_b = b(n-k);
        long term = sopfk * right_b;
        result += term;
    }
    result /= n;

    cache[n] = result;
    return result;
}

} // end namespace anonymous

void pe77::run()
{
    /*
     * It is possible to write ten as the sum of primes in exactly five
     * different ways:
     *
     *   7 + 3
     *   5 + 5
     *   5 + 3 + 2
     *   3 + 3 + 2 + 2
     *   2 + 2 + 2 + 2 + 2
     *
     * What is the first value which can be written as the sum of primes
     * in over five thousand different ways?
     *
     */

    long limit = 5000;
    for ( long n = 0; n < limit; ++n )
    {
        long result = b(n);
        if ( result > limit )
        {
            std::cout << n << ", " << result << std::endl;
            break;
        }
    }
}
