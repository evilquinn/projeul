/*
 * pe41.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe41.hpp"
#include <stdio.h>
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

std::string& pe41::name() { return name_; }
void         pe41::run()
{
    /*
     * We shall say that an n-digit number is pandigital if it makes use of
     * all the digits 1 to n exactly once. For example, 2143 is a 4-digit
     * pandigital and is also prime.
     *
     * What is the largest n-digit pandigital prime that exists?
     *
     */

    primes_    = prime_sieve( 8000000 );
    int result = 1;

    for ( size_t i = 8000000; i > 1; --i )
    {
        int d = num_digits( i );
        if ( primes_.is_prime( i ) && is_pandigital_for_range( 1, d, &i, 1 ) )
        {
            result = i;
            break;
        }
    }
    std::cout << name() << " " << result << std::endl;
}
