/*
 * pe78.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/typeof/typeof.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <pe78.hpp>
#include <utils.hpp>

std::string& pe78::name() { return name_; }

namespace bmp = boost::multiprecision;

namespace
{  // anonymous

template <unsigned int Base>
long divisor_f( long n )
{
    std::map<long, long> cache;
    if ( cache[n] > 0 )
    {
        return cache[n];
    }

    long result = 0;
    for ( long d = 1; d <= n; ++d )
    {
        if ( n % d == 0 )
        {
            result += pow( d, Base );
        }
    }

    cache[n] = result;
    return result;
}

long a( long ) { return 1; }

long c( long n )
{
    std::map<long, long> cache;
    if ( cache[n] > 0 )
    {
        return cache[n];
    }

    long result = 0;
    for ( long d = 1; d <= n; ++d )
    {
        if ( n % d == 0 )
        {
            result += d * a( d );
        }
    }

    cache[n] = result;
    return result;
}

long pentagonal_of( long n ) { return n * ( ( 3 * n ) - 1 ) / 2; }

}  // namespace

void pe78::run()
{
    /*
     *
     * Let p(n) represent the number of different ways in which n coins can
     * be separated into piles. For example, five coins can be separated
     * into piles in exactly seven different ways, so p(5)=7.
     *
     *   OOOOO
     *   OOOO   O
     *   OOO   OO
     *   OOO   O   O
     *   OO   OO   O
     *   OO   O   O   O
     *   O   O   O   O   O
     *
     * Find the least value of n for which p(n) is divisible by one million.
     *
     * Eugh.  Simply couldn't have solved this one without
     * https://www.mathblog.dk/project-euler-78-coin-piles/
     * Big thanks.
     *
     */

    long limit              = 1000000;
    long goal               = 1000000;
    long n                  = 1;
    std::vector<long> terms = { 1 };
    for ( ; n <= limit; ++n )
    {
        long subee = 1;
        long k     = 0;
        terms.push_back( 0 );
        while ( subee <= n )
        {
            long sign = ( k % 4 > 1 ) ? -1 : 1;
            terms[n] += sign * terms[n - subee];
            terms[n] %= goal;
            ++k;
            long next = ( k % 2 == 0 ) ? k / 2 + 1 : -1 * ( k / 2 + 1 );
            subee     = next * ( 3 * next - 1 ) / 2;
        }
        if ( terms[n] == 0 || n == limit )
        {
            std::cout << n << ", " << terms[n] << std::endl;
            break;
        }
    }
}
