/*
 * pe71.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <iostream>
#include <map>
#include <pe71.hpp>
#include <utils.hpp>

std::string& pe71::name() { return name_; }
void pe71::run()
{
    /*
     * Consider the fraction, n/d, where n and d are positive integers.
     * If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
     *
     * If we list the set of reduced proper fractions for d ≤ 8 in ascending
     * order of size, we get:
     *
     * 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5,i
     * 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
     *
     * It can be seen that 2/5 is the fraction immediately to the left of 3/7.
     *
     * By listing the set of reduced proper fractions for d ≤ 1,000,000 in
     * ascending order of size, find the numerator of the fraction
     * immediatelyi
     * to the left of 3/7.
     *
     */

    size_t limit = 1000000;
    std::map<double, std::pair<size_t, size_t> > resultm;

    double ubound = (double)3 / 7;
    double lbound = (double)2 / 5;

    bool finished = false;
    size_t seen   = 0;
    for ( size_t d = limit; d > 0; --d )
    {
        for ( size_t n = ( d * 3 ) / 7; n < d; ++n )
        {
            double key = (double)n / d;
            if ( key < ubound && key > lbound )
            {
                if ( gcd( n, d ) == 1 )
                {
                    lbound = key;
                    resultm.insert(
                        std::make_pair( key, std::make_pair( n, d ) ) );
                    ++seen;
                    if ( seen == 2 )
                    {
                        finished = true;
                    }
                    break;
                }
            }
        }
        if ( finished )
        {
            break;
        }
    }

    for ( auto e : resultm )
    {
        std::cout << e.second.first << "/" << e.second.second << ", ";
    }
    std::cout << std::endl;
}
