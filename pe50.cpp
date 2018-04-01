/*
 * pe50.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe50.hpp"
#include <ctype.h>
#include <stdio.h>
#include <boost/foreach.hpp>
#include <cmath>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

#define PE50_LIMIT 1000000

std::string& pe50::name() { return name_; }
void         pe50::run()
{
    /*
     *
     * Problem 50 - Consecutive Prime Sum
     *
     * The prime 41, can be written as the sum of six consecutive primes:
     *
     *     41 = 2 + 3 + 5 + 7 + 11 + 13
     *
     * This is the longest sum of consecutive primes that adds to a prime
     * below one-hundred.
     *
     * The longest sum of consecutive primes below one-thousand that adds
     * to a prime, contains 21 terms, and is equal to 953.
     *
     * Which prime, below one-million, can be written as the sum of the most
     * consecutive primes?
     *
     */
    primes_              = prime_sieve( PE50_MAX_PRIMES );
    size_t hard_limit    = 1000000;
    size_t working_limit = 4000;
    size_t upper         = primes_.prev_prime( working_limit );
    size_t lower         = primes_.next_prime( 0 );

    size_t best_range    = 0;
    size_t working_range = 0;
    size_t best_sum      = 0;
    size_t working_sum   = 0;

    while ( lower < upper )
    {
        upper = primes_.prev_prime( working_limit );
        while ( upper > lower )
        {
            working_sum = primes_.sum_range( lower, upper, working_range );
            if ( working_sum > hard_limit )
            {
                working_limit = upper;
                upper         = primes_.prev_prime( upper );
                continue;
            }
            if ( working_range < best_range )
            {
                break;
            }
            if ( primes_.is_prime( working_sum ) &&
                 working_range > best_range )
            {
                best_range = working_range;
                best_sum   = working_sum;
                break;
            }

            upper = primes_.prev_prime( upper );
        }

        lower = primes_.next_prime( lower );
    }

    std::cout << "best     : " << best_sum << std::endl;
    std::cout << "best size: " << best_range << std::endl;
}
