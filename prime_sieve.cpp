/*
 * prime_sieve.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "prime_sieve.hpp"

#include <string.h>
#include <iostream>

prime_sieve::prime_sieve(int max) :
    limit_(max),
    sieve_(new bool[limit_+1])
{
    memset(sieve_, true, sizeof(bool) * (limit_ + 1));
    sieve_[0] = false; // indices represent numbers, 0 isn't prime
    sieve_[1] = false; // indices represent numbers, 1 isn't prime

    calc_primes();
}

prime_sieve::~prime_sieve()
{
    delete[] sieve_;
}

void prime_sieve::calc_primes()
{
    int n = 2;
    while ( n < limit_ )
    {
        if ( sieve_[n] )
        {
            for ( int i = n + n; i < limit_; i += n )
            {
                sieve_[i] = false;
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
    for ( int i = 1; i < limit_; ++i)
    {
        if ( sieve_[i] )
        {
            std::cout << i << std::endl;
        }
    }
}

bool prime_sieve::is_prime(int n)
{
    if ( n > 0 && n < limit_ )
    {
        return sieve_[n];
    }

    return false;
}
