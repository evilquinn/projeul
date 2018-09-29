/*
 * pe49.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe49.hpp"
#include <boost/foreach.hpp>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

#define PE49_NUM_DIGITS 10

size_t next_prime_with_same_digits( size_t start, prime_sieve& primes );

std::string& pe49::name() { return name_; }
void pe49::run()
{
    /*
     *
     * The arithmetic sequence, 1487, 4817, 8147, in which each of the terms
     * increases by 3330, is unusual in two ways:
     *   (i) each of the three terms are prime, and,
     *   (ii) each of the 4-digit numbers are permutations of one another.
     *
     * There are no arithmetic sequences made up of three 1-, 2-, or 3-digit
     * primes, exhibiting this property, but there is one other 4-digit
     * increasing sequence.
     *
     * What 12-digit number do you form by concatenating the three terms in
     * this sequence?
     *
     */
    primes_      = prime_sieve( PE49_MAX_PRIMES );
    size_t first = 1487;
    size_t second;
    size_t third;
    bool solved = false;

    do
    {
        first = next_prime( primes_, first );
        if ( first == 0 )
        {
            break;
        }

        second = first;
        do
        {
            second = next_prime_with_same_digits( second, primes_ );
            if ( second <= first )
            {
                break;
            }

            third = second + second - first;

            if ( third < PE49_MAX_PRIMES && primes_.is_prime( third ) &&
                 same_digits( second, third ) )
            {
                solved = true;
            }
        } while ( !solved && second < PE49_MAX_PRIMES );
    } while ( !solved && first < PE49_MAX_PRIMES );

    std::cout << name() << " " << first << second << third << std::endl;
}

size_t next_prime_with_same_digits( size_t start, prime_sieve& primes )
{
    size_t result = start;
    do
    {
        result = next_prime( primes, result );
    } while ( result != 0 && !same_digits( start, result ) );

    return result;
}
