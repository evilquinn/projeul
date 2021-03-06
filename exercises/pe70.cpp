/*
 * pe70.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <iostream>
#include <pe70.hpp>
#include <prime_sieve.hpp>
#include <set>
#include <utils.hpp>

std::string& pe70::name() { return name_; }
void pe70::run()
{
    /*
     *
     *
     * Euler's Totient function, φ(n) [sometimes called the phi function],
     * is used to determine the number of positive numbers less than or equal
     * to n which are relatively prime to n. For example, as 1, 2, 4, 5, 7,
     * and 8, are all less than nine and relatively prime to nine, φ(9)=6.
     * The number 1 is considered to be relatively prime to every positive
     * number, so φ(1)=1.
     *
     * Interestingly, φ(87109)=79180, and it can be seen that 87109 is a
     * permutation of 79180.
     *
     * Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of
     * n and the ratio n/φ(n) produces a minimum.
     */

    size_t limit = 10000000;
    prime_sieve primes( limit + 1 );
    size_t result  = 0;
    double minimum = 1000;
    for ( size_t i = 1000000; i <= limit; ++i )
    {
        if ( primes.is_prime( i ) )
        {
            continue;
        }
        bool prime_divisor = false;
        for ( size_t pr = primes.next_prime( 1 ); pr < 1000;
              pr        = primes.next_prime( pr ) )
        {
            if ( i % pr == 0 )
            {
                prime_divisor = true;
                break;
            }
        }
        if ( prime_divisor )
        {
            // apparently, no point checking nums which are divisible by
            // the smaller primes!
            continue;
        }
        auto prifacs = calc_prime_factors( i, primes );
        std::set<size_t> dedup( prifacs.begin(), prifacs.end() );
        size_t total = i;
        for ( size_t p : dedup )
        {
            total *= p - 1;
            total /= p;
        }

        if ( is_permutation( total, i ) )
        {
            double attempt = i / static_cast<double>( total );
            // std::cout << relper.size() << std::endl;
            if ( attempt < minimum )
            {
                minimum = attempt;
                result  = i;
            }
        }
    }

    std::cout << result << ", " << minimum << std::endl;
}
