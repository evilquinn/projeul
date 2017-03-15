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

size_t prod_of_num_array(size_t* num, size_t num_nums);

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

    primes_ = prime_sieve(PE47_NUM_PRIMES);
    const size_t n = 4;

    size_t found_n_consecutives = 0;
    size_t num = 1;
    while(found_n_consecutives < n && num < 1000000)
    {
        if(num_has_n_distinct_prime_factors(num, n))
        {
            ++found_n_consecutives;
        }
        else
        {
            found_n_consecutives = 0;
        }
        ++num;
    }

    std::cout << "PE47 " << num-n << std::endl;
}

bool pe47::num_has_n_distinct_prime_factors(size_t num, size_t n)
{
    std::vector<size_t> prime_factors;
    calc_prime_factors(num, prime_factors, primes_);

    std::set<size_t> distinct_prime_factors(prime_factors.begin(),
                                            prime_factors.end());

    if( n == distinct_prime_factors.size() )
    {
        return true;
    }

    return false;
}

size_t calc_prime_factors(size_t num,
                          std::vector<size_t>& prime_factors,
                          prime_sieve& primes)
{

    // try dividing num by 2, then 3, then 5, etc, etc
    // each time a division works (no remainders), cache the
    // prime factor, and move on to working out the next prime
    // factor, starting dividing from the first prime again
    //
    size_t curr_num = num;

    while(curr_num > 1)
    {
        if(primes.is_prime(curr_num))
        {
            prime_factors.push_back(curr_num);
            break;
        }

        size_t try_prime = 2;
        while(curr_num % try_prime != 0)
        {
            try_prime = next_prime(try_prime, primes);
        }

        prime_factors.push_back(try_prime);
        curr_num /= try_prime;
    }

//    std::cout << "prime factors of " << num << " are ";
//    BOOST_FOREACH(size_t i, prime_factors )
//    {
//        std::cout << i << ", ";
//    }
//    std::cout << std::endl;

    return 0;

}


