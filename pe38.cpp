/*
 * pe38.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe38.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>

int num_digits_array(long long unsigned* ints, int ints_size);

std::string& pe38::name()
{
    return name_;
}

void pe38::run()
{
    /*
     * Take the number 192 and multiply it by each of 1, 2, and 3:
     *
     *     192 × 1 = 192
     *     192 × 2 = 384
     *     192 × 3 = 576
     *
     * By concatenating each product we get the 1 to 9 pandigital, 192384576.
     * We will call 192384576 the concatenated product of 192 and (1,2,3)
     *
     * The same can be achieved by starting with 9 and multiplying by
     * 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the
     * concatenated product of 9 and (1,2,3,4,5).
     *
     * What is the largest 1 to 9 pandigital 9-digit number that can be formed
     * as the concatenated product of an integer with
     * (1,2, ... , n) where n > 1?
     */
    int largest = 0;
    int range_start = 1;
    int range_end   = 9;
    int range       = range_end - range_start + 1;
    long unsigned i_limit = 10000;
    for(long unsigned i = 9; i < i_limit; ++i)
    {
        int n_limit = 10;
        for( int n = 2; n < n_limit; ++n)
        {
            int ints[n];
            long long unsigned lluints[n];
            for(int to_n = 0; to_n < n; ++to_n)
            {
                ints[to_n] = i*(to_n+1);
                lluints[to_n] = i*(to_n+1);
            }

            if ( num_digits_array(lluints, n) != range )
            {
                continue;
            }

            if ( is_pandigital_for_range(range_start,
                                         range_end,
                                         ints,
                                         n) )
            {
                std::cout << "prod of " << i
                          << " and (";
                for(int i = 0; i<n;++i)
                {
                    std::cout << i+1 << ",";
                }
                std::cout << ") = ";
                for(int i=0;i<n;++i)
                {
                    std::cout << ints[i];
                }
                std::cout << " is pandigital" << std::endl;


            }
        }
    }

    std::cout << "PE38 " << largest << std::endl;
}

int num_digits_array(long long unsigned* ints, int ints_size)
{
    int total = 0;
    for(int i=0;i<ints_size;++i)
    {
        total += num_digits(ints[i]);
    }
    return total;
}
