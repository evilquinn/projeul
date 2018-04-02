/*
 * pe35.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe35.hpp"
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <utils.hpp>

int cycle_ints( int n );

std::string& pe35::name() { return name_; }
void         pe35::run()
{
    /*
     *
     * The number 197 is called a circular prime because all rotations of
     * the digits: 197, 971, and 719, are themselves prime.
     *
     * There are thirteen such primes below 100:
     * 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
     *
     * How many circular primes are there below one million?
     *
     */
    primes_   = prime_sieve( 1000000 );
    int total = 0;
    for ( int i = 2; i < 1000000; ++i )
    {
        bool done        = false;
        int  curr        = i;
        bool is_circular = true;
        while ( !done )
        {
            if ( !primes_.is_prime( curr ) )
            {
                is_circular = false;
                break;
            }
            curr = cycle_ints( curr );
            if ( curr == i )
            {
                done = true;
            }
        }

        if ( is_circular )
        {
            ++total;
        }
    }

    std::cout << name() << " " << total << std::endl;
}

int cycle_ints( int n )
{
    int last = n % 10;
    int w    = n / 10;
    return w + ( last * ( pow( 10, num_digits( w ) ) ) );
}
