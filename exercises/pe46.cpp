/*
 * pe46.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe46.hpp"
#include <ctype.h>
#include <stdio.h>
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

size_t prev_prime( size_t i, prime_sieve& primes );

std::string& pe46::name() { return name_; }
void pe46::run()
{
    /*
     *
     *
     * It was proposed by Christian Goldbach that every odd composite number
     * can be written as the sum of a prime and twice a square.
     *
     * 9 = 7 + 2×1^2
     * 15 = 7 + 2×2^2
     * 21 = 3 + 2×3^2
     * 25 = 7 + 2×3^2
     * 27 = 19 + 2×2^2
     * 33 = 31 + 2×1^2
     *
     * It turns out that the conjecture was false.
     *
     * What is the smallest odd composite that cannot be written as the sum of
     * a prime and twice a square?
     *
     */

    primes_       = prime_sieve( PE46_NUM_PRIMES );
    squares_      = std::vector<size_t>( PE46_NUM_PRIMES );
    size_t result = 0;

    for ( size_t i = 1; i <= PE46_NUM_PRIMES; ++i )
    {
        squares_[i] = pow( i, 2 );
    }

    for ( size_t i = 35; i < 10000; i += 2 )
    {
        if ( !primes_.is_prime( i ) )
        {
            if ( !fulfills_goldbachs_conjecture( i ) )
            {
                result = i;
                break;
            }
        }
    }

    std::cout << name() << " " << result << std::endl;
}

bool pe46::fulfills_goldbachs_conjecture( size_t i )
{
    size_t prev = i;
    do
    {
        prev = prev_prime( prev, primes_ );
        if ( prev == 2 )
        {
            continue;
        }
        size_t diff        = i - prev;
        size_t poss_square = diff / 2;
        if ( std::binary_search(
                 squares_.begin(), squares_.end(), poss_square ) )
        {
            return true;
        }
    } while ( prev > 2 );

    return false;
}

size_t prev_prime( size_t i, prime_sieve& primes )
{
    if ( i <= 2 )
    {
        return 0;
    }

    do
    {
        --i;
    } while ( i > 2 && !primes.is_prime( i ) );
    return i;
}
