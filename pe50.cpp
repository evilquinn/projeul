/*
 * pe50.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe50.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>

size_t number_consecutive_primes_sum(size_t num, prime_sieve& primes);

std::string& pe50::name()
{
    return name_;
}

void pe50::run()
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
    size_t start = 0;
    size_t most_primes = 0;
    size_t result = 0;

    std::vector<size_t> longest_sum;
    size_t sum = 0;

    do
    {
        start = next_prime(start, primes_);
        longest_sum.push_back(start);
        sum += start;
    }
    while(sum < 1000000);

    do
    {
        sum -= longest_sum.back();
        longest_sum.pop_back();
    }
    while(!primes_.is_prime(sum));


    std::cout << "PE50 " << sum << " has " << longest_sum.size() << std::endl;
}

size_t sum_vector(std::vector<size_t>& vec)
{
    size_t result = 0;
    BOOST_FOREACH(size_t val, vec)
    {
        result += val;
    }

    return result;
}

