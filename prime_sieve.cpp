/*
 * prime_sieve.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "prime_sieve.hpp"

#include <string.h>
#include <iostream>

prime_sieve::prime_sieve(size_t max) :
    limit_(max),
    sieve_()
{
    // set all valid, we'll mark off the ones not prime
    sieve_.set();

    // 0 and 1 aren't prime
    sieve_.reset(0);
    sieve_.reset(1);

    calc_primes();
}

prime_sieve::~prime_sieve()
{
}

void prime_sieve::calc_primes()
{
    size_t n = 2;
    while ( n < limit_ )
    {
        if ( sieve_[n] )
        {
            for ( size_t i = n + n; i < limit_; i += n )
            {
                sieve_.reset(i);
            }
        }

        do
        {
            // increment, skipping the one's already marked
            ++n;
        }
        while( !sieve_[n] );
    }
}

void prime_sieve::print()
{
    for ( size_t i = 1; i < limit_; ++i)
    {
        if ( sieve_[i] )
        {
            std::cout << i << std::endl;
        }
    }
}

bool prime_sieve::is_prime(size_t n)
{
    if ( n > 0 && n < limit_ )
    {
        return sieve_[n];
    }

    return false;
}
