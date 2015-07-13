/*
 * pe47.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe47.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>

size_t next_prime(size_t i, prime_sieve& primes);

std::string& pe47::name()
{
    return name_;
}

void pe47::run()
{
    /*
     *
     * The first two consecutive numbers to have two distinct prime factors
     * are:
     *
     * 14 = 2 × 7
     * 15 = 3 × 5
     *
     * The first three consecutive numbers to have three distinct prime
     * factors are:
     *
     * 644 = 2 × 7 × 23
     * 645 = 3 × 5 × 43
     * 646 = 2 × 17 × 19.
     *
     * Find the first four consecutive integers to have four distinct prime
     * factors. What is the first of these numbers?
     *
     */

    size_t result = 0;
    const size_t n = 2;

    for(size_t i = 1; i < 20; ++i)
    {
        if(n_consecutive_nums_have_n_distinct_prime_factors(i, n))
        {
            result = i;
            break;
        }
    }

    std::cout << "PE47 " << result << std::endl;
}

bool pe47::n_consecutive_nums_have_n_distinct_prime_factors(size_t first,
                                                            size_t n)
{


    return false;
}

bool pe47::num_has_n_distinct_prime_factors(size_t num, size_t n)
{
    if ( n < 1 )
    {
        return false;
    }

    // populate the array of n prime factor candidates
    size_t try_primes[n];
    // init
    try_primes[0] = 0;
    increment_array_primes_first_n_fixed(try_primes, n, primes_, 0);

    size_t prod = prod_of_num_array(try_primes, n);
    int diff = num - prod;
    size_t num_fixed = n - 1;

    if(diff == 0)
    {
        return true;
    }
    if(diff < 0)
    {
        if(num_fixed == 0)
        {
            return false;
        }
        --num_fixed;
    }

    increment_array_primes_first_n_fixed(try_primes, num_fixed

    diff = 


    int inc_idx = n - 1;

    while(inc_idx >= 0)
    {
        prod = prod_of_num_array(try_primes, n);
        if(prod>num)
        {
            --inc_idx;
            continue;
        }



    }

    return false;
}

size_t prod_of_num_array(size_t* num, size_t num_nums)
{
    size_t result = 1;
    do
    {
        result *= nums[num_nums-1];
        --num_nums;
    }
    while(num_nums>0);
    return result;
}

size_t next_prime(size_t i, prime_sieve& primes)
{
    if ( i >= PE47_NUM_PRIMES )
    {
        return 0;
    }

    do
    {
        ++i;
    }
    while( i < PE47_NUM_PRIMES && ! primes.is_prime(i) );

    return i;
}

void increment_array_primes_first_n_fixed(size_t*      nums,
                                          size_t       num_nums,
                                          prime_sieve& primes,
                                          size_t       n)
{
    if(n>=num_nums)
    {
        return;
    }

    nums[n] = next_prime(nums[n], primes);
    ++n;
    while(n<num_nums)
    {
        nums[n] = next_prime(nums[n-1]);
        ++n;
    }
}








