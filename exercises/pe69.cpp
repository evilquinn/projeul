/*
 * pe69.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe69.hpp>
#include <iostream>
#include <set>
#include <utils.hpp>
#include <prime_sieve.hpp>

std::string& pe69::name() { return name_; }

void         pe69::run()
{
    /*
     * Euler's Totient function, φ(n) [sometimes called the phi function],
     * is used to determine the number of numbers less than n which are
     * relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are
     * all less than nine and relatively prime to nine, φ(9)=6.
     *
     * n    Relatively Prime    φ(n)    n/φ(n)
     * 2    1                   1       2
     * 3    1,2                 2       1.5
     * 4    1,3                 2       2
     * 5    1,2,3,4             4       1.25
     * 6    1,5                 2       3
     * 7    1,2,3,4,5,6         6       1.1666...
     * 8    1,3,5,7             4       2
     * 9    1,2,4,5,7,8         6       1.5
     * 10   1,3,7,9             4       2.5
     *
     * It can be seen that n=6 produces a maximum n/φ(n) for n ≤ 10.
     *
     * Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum.
     */

    size_t limit = 1000000;
    prime_sieve primes(limit+1);
    double result = 0;
    double biggest_attempt = 0;
    for ( size_t i = 6; i <= limit; ++i )
    {
        if ( primes.is_prime(i) )
        {
            continue;
        }
        auto prifacs = calc_prime_factors(i, primes);
        std::set<size_t> deup(prifacs.begin(), prifacs.end());
        double total = i;
        for ( double p: deup )
        {
            total *= ( 1 - 1/p );
        }
        double attempt = i / total;
        //std::cout << relper.size() << std::endl;
        if ( attempt > biggest_attempt )
        {
            biggest_attempt = attempt;
            result = i;
        }
    }

    std::cout << (size_t)result << std::endl;

}
