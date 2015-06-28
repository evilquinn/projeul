/*
 * pe37.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe37.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>



std::string& pe37::name()
{
    return name_;
}

void pe37::run()
{
    /*
     *
     * The number 3797 has an interesting property. Being prime itself, it is
     * possible to continuously remove digits from left to right, and remain
     * prime at each stage: 3797, 797, 97, and 7. Similarly we can work from
     * right to left: 3797, 379, 37, and 3.
     *
     * Find the sum of the only eleven primes that are both truncatable from
     * left to right and right to left.
     *
     * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
     *
     */

    int total = 0;

    for(int i = 11; i<1000000; ++i)
    {
        if( is_trunc_prime(i) )
        {
            std::cout << i << " wins" << std::endl;
            total += i;
        }
    }

    std::cout << "PE37 " << total << std::endl;
}

bool pe37::is_trunc_prime_rtl(int n)
{
    if( ! primes_.is_prime(n) )
    {
        return false;
    }

    if( n/10 > 0 )
    {
        int new_n = n/10;
        return is_trunc_prime_rtl( new_n );
    }

    return true;
}

bool pe37::is_trunc_prime_ltr(int n)
{
    if( ! primes_.is_prime(n) )
    {
        return false;
    }

    if( n/10 > 0 )
    {
        int num_digits_n = num_digits(n);
        int num_digits_new_n = num_digits_n-1;
        int mod_factor = pow(10, num_digits_new_n );
        int new_n = n%mod_factor;
        if(num_digits(new_n) != num_digits_new_n)
        {
            //leading zero, chuck
            return false;
        }
        return is_trunc_prime_ltr( new_n );
    }

    return true;
}

bool pe37::is_trunc_prime(int n)
{
    return is_trunc_prime_rtl(n) && is_trunc_prime_ltr(n);
}



