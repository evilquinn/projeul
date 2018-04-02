/*
 * pe27.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe27.hpp"
#include <cmath>
#include <iostream>

std::string& pe27::name() { return name_; }
void         pe27::run()
{
    /*
     * Considering quadratics of the form:
     *
     * n² + an + b, where |a| < 1000 and |b| < 1000
     *
     * where |n| is the modulus/absolute value of n
     * e.g. |11| = 11 and |−4| = 4
     *
     */
    if ( primes_ == nullptr )
    {
        primes_ = new prime_sieve( 1000000 );
    }
    int most_number_primes = 0;
    int super_a            = 0;
    int super_b            = 0;
    for ( int a = -999; a < 1000; ++a )
    {
        for ( int b = -999; b < 1000; ++b )
        {
            int  i                    = 0;
            int  current_count_primes = 0;
            bool done                 = false;
            while ( !done )
            {
                double current_result = ( pow( i, 2 ) ) + ( a * i ) + b;
                // std::cout << "testing: " << current_result << std::endl;
                if ( !primes_->is_prime( current_result ) )
                {
                    done = true;
                }
                else
                {
                    ++current_count_primes;
                    ++i;
                }
            }
            if ( current_count_primes > most_number_primes )
            {
                most_number_primes = current_count_primes;
                super_a            = a;
                super_b            = b;
            }
        }
    }

    int result = super_a * super_b;
    std::cout << name() << ": " << result << std::endl;
}
