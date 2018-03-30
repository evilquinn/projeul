/*
 * pe30.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe30.hpp"
#include <cmath>
#include <iostream>
#include <set>

int sum_pow_digits( int n, int power );

std::string& pe30::name() { return name_; }
void         pe30::run()
{
    /*
     *
     * Surprisingly there are only three numbers that can be written as
     * the sum of fourth powers of their digits:
     *
     *     1634 = 1^4 + 6^4 + 3^4 + 4^4
     *     8208 = 8^4 + 2^4 + 0^4 + 8^4
     *     9474 = 9^4 + 4^4 + 7^4 + 4^4
     *
     * As 1 = 1^4 is not a sum it is not included.
     *
     * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
     *
     * Find the sum of all the numbers that can be written as the sum of
     * fifth powers of their digits.
     *
     */

    const int super_power = 5;
    double    total_sum   = 0;

    for ( int i = 10; i < 400000; ++i )
    {
        double res = sum_pow_digits( i, super_power );
        if ( i == res )
        {
            total_sum += res;
        }
    }

    std::cout << "PE30: " << total_sum << std::endl;
}

int sum_pow_digits( int n, int power )
{
    int left = n / 10;
    int sum  = pow( n % 10, power );
    while ( left > 0 )
    {
        sum += pow( left % 10, power );
        left /= 10;
    }

    return sum;
}
