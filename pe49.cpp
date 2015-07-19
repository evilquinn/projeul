/*
 * pe49.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe49.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>

#define PE49_NUM_DIGITS 10


size_t next_prime_with_same_digits(size_t start, prime_sieve& primes);
bool same_digits(size_t lhs, size_t rhs);

std::string& pe49::name()
{
    return name_;
}

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
    size_t first = next_prime(1000, primes_);
    size_t second = next_prime_with_same_digits(first, primes_);




    std::cout << "PE49 " << first << second << std::endl;
}

size_t next_prime_with_same_digits(size_t start, prime_sieve& primes)
{
    size_t result = start;
    do
    {
        result = next_prime(result, primes);
    }
    while(!same_digits(start, result));

    return result;
}

bool same_digits(size_t lhs, size_t rhs)
{
    std::multiset<uint8_t> lhs_digits;
    unsigned expected_count = 0;
    unsigned compare_count = 0;
    while(lhs>0)
    {
        lhs_digits.insert(lhs%10);
        lhs /= 10;
        ++expected_count;
    }

    while(rhs>0)
    {
        auto it = lhs_digits.find(rhs%10);
        if ( it != lhs_digits.end() )
        {
            lhs_digits.erase(it);
            ++compare_count;
            rhs /= 10;
        }
        else
        {
            return false;
        }
    }

    return expected_count == compare_count;
}

