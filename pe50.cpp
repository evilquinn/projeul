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

#define PE50_LIMIT 1000

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

    std::vector<size_t> max_list;
    size_t sum = 0;

    // work out a good start point, which is every prime when summed is greater
    // than limit
    do
    {
        start = next_prime(start, primes_);
        max_list.push_back(start);
        sum += start;
    }
    while(sum < PE50_LIMIT);

    // work out a reasonable first guess, count back the primes until the sum
    // is prime
    std::vector<size_t> starting_list = max_list;
    do
    {
        sum -= starting_list.back();
        starting_list.pop_back();
    }
    while(!primes_.is_prime(sum));

    // now examine all possible better solutions
    std::vector<size_t> curr_list = max_list;
    size_t starting_size = max_list.size();
    size_t starting_sum = sum;
    size_t result_size = 0;
    std::vector<size_t> result_list;
    do
    {
        starting_sum -= curr_list[0];
        curr_list.erase(curr_list.begin());
        --starting_size;
        size_t curr_sum = starting_sum;
        do
        {
            if(curr_sum < PE50_LIMIT &&
               primes_.is_prime(curr_sum) &&
               curr_list.size() > result_size &&
               curr_sum > sum )
            {
                sum = curr_sum;
                result_size = curr_list.size();
                result_list = curr_list;
                break;
            }

            curr_sum -= curr_list.back();
            curr_list.pop_back();
        }
        while(curr_list.size() > max_list.size());
    }
    while(starting_size > starting_list.size());

    std::cout << "PE50 " << sum << " has " << result_size << " : " << std::endl;
    BOOST_FOREACH(size_t val, result_list)
    {
        std::cout << val << " ";
    }
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

