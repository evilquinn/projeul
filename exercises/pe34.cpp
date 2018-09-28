/*
 * pe34.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe34.hpp"
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>

int fac( int n );

std::string& pe34::name() { return name_; }
void pe34::run()
{
    /*
     * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
     *
     * Find the sum of all numbers which are equal to the sum of the factorial
     * of their digits.
     *
     * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
     *
     */
    int facs[] = { fac( 0 ), fac( 1 ), fac( 2 ), fac( 3 ), fac( 4 ),
                   fac( 5 ), fac( 6 ), fac( 7 ), fac( 8 ), fac( 9 ) };

    int sum_all_facs = 0;
    for ( int i = 145; i < 50000; ++i )
    {
        int left     = i;
        int sum_facs = 0;
        while ( left > 0 )
        {
            sum_facs += facs[left % 10];
            left /= 10;
        }

        if ( i == sum_facs )
        {
            sum_all_facs += sum_facs;
            std::cout << i << std::endl;
        }
    }

    std::cout << name() << " " << sum_all_facs << std::endl;
}

int fac( int n )
{
    if ( n == 0 )
    {
        return 1;
    }
    int fac = 1;
    for ( int i = 2; i <= n; ++i )
    {
        fac *= i;
    }
    return fac;
}
