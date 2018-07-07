/*
 * pe73.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <iostream>
#include <map>
#include <pe73.hpp>
#include <utils.hpp>

std::string& pe73::name() { return name_; }
void         pe73::run()
{
    /*
     * Consider the fraction, n/d, where n and d are positive integers.
     * If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
     *
     * If we list the set of reduced proper fractions for d ≤ 8 in ascendingi
     * order of size, we get:
     *
     * 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7,
     * 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
     *
     * It can be seen that there are 3 fractions between 1/3 and 1/2.
     *
     * How many fractions lie between 1/3 and 1/2 in the sorted set of reduced
     * proper fractions for d ≤ 12,000?
     *
     *
     */

    size_t limit  = 12000;
    size_t result = 0;

    double ubound = (double)1 / 2;
    double lbound = (double)1 / 3;

    for ( size_t d = 2; d <= limit; ++d )
    {
        for ( size_t n = d / 3; n < ( d + 1 ) / 2; ++n )
        {
            double key = (double)n / d;
            if ( key < ubound && key > lbound )
            {
                if ( gcd( n, d ) == 1 )
                {
                    ++result;
                }
            }
        }
    }

    std::cout << result << std::endl;
}
