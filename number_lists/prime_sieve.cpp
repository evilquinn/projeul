/*
 * prime_sieve.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "prime_sieve.hpp"
#include <utils.hpp>

#include <string.h>
#include <iostream>

prime_sieve::prime_sieve( size_t limit ) : limit_( limit ), sieve_( limit )
{
    // set all valid, we'll mark off the ones not prime
    sieve_.set();

    // 0 and 1 aren't prime
    sieve_.reset( 0 );
    sieve_.reset( 1 );

    std::cout << "Calc'ing all primes from 2 to " << limit_ << " ... "
              << std::endl;

    calc_primes();

    std::cout << "Done." << std::endl;
}

prime_sieve::~prime_sieve() = default;
size_t prime_sieve::limit() { return limit_; }
void   prime_sieve::calc_primes()
{
    size_t n = 2;
    while ( n < limit_ )
    {
        if ( sieve_[n] )
        {
            for ( size_t i = n + n; i < limit_; i += n )
            {
                sieve_.reset( i );
            }
        }

        n = sieve_.find_next( n );
    }
}

void prime_sieve::print()
{
    for ( size_t i = 1; i < limit_; ++i )
    {
        if ( sieve_[i] )
        {
            std::cout << i << std::endl;
        }
    }
}

bool prime_sieve::is_prime( size_t n )
{
    if ( n > limit_ )
    {
        return ::is_prime( *this, n );
    }
    return sieve_[n];
}

size_t prime_sieve::next_prime( size_t from )
{
    size_t result = sieve_.find_next( from );
    if ( result == sieve_.npos )
    {
        return ::next_prime( *this, from );
    }
    return result;
}

size_t prime_sieve::prev_prime( size_t from )
{
    if ( --from >= limit_ )
    {
        return 0;
    }

    size_t result;
    for ( result = from; !sieve_[result] && result != 0; --result )
    {
    }

    return result;
}

size_t prime_sieve::num_in_range( size_t lower, size_t upper )
{
    lower = is_prime( lower ) ? lower : next_prime( lower );
    upper = is_prime( upper ) ? upper : prev_prime( upper );

    if ( lower > upper )
    {
        return 0;
    }
    if ( lower == upper )
    {
        return 1;
    }
    size_t result = 0;
    do
    {
        ++result;
        lower = next_prime( lower );
    } while ( lower <= upper );

    return result;
}

size_t prime_sieve::sum_range( size_t  lower,
                               size_t  upper,
                               size_t& num_in_range )
{
    if ( lower > upper )
    {
        return 0;
    }
    if ( lower == upper )
    {
        if ( is_prime( lower ) )
        {
            num_in_range = 1;
            return lower;
        }

        return 0;
    }

    size_t current;
    current = is_prime( lower ) ? lower : next_prime( lower );

    size_t result = 0;
    num_in_range  = 0;

    while ( current <= upper && current < limit_ )
    {
        result += current;
        ++num_in_range;
        current = next_prime( current );
    }

    return result;
}

size_t prime_sieve::shit_sum_range( size_t              lower,
                                    size_t              upper,
                                    std::deque<size_t>& sumees )
{
    sumees.clear();

    if ( lower > upper )
    {
        return 0;
    }
    if ( lower == upper )
    {
        if ( is_prime( lower ) )
        {
            sumees.push_back( lower );
            return lower;
        }

        return 0;
    }

    size_t current;
    current = is_prime( lower ) ? lower : next_prime( lower );

    size_t result = 0;

    while ( current <= upper && current < limit_ )
    {
        result += current;
        sumees.push_back( current );
        current = next_prime( current );
    }

    return result;
}
