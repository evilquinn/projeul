/*
 * pe44.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe44.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>


std::string& pe44::name()
{
    return name_;
}

void pe44::run()
{
    /*
     * Pentagonal numbers are generated by the formula, P(n) = n(3n−1)/2.
     * The first ten pentagonal numbers are:
     *
     *     1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
     *
     * It can be seen that P(4) + P(7) = 22 + 70 = 92 = P(8). However, their
     * difference, 70 − 22 = 48, is not pentagonal.
     *
     * Find the pair of pentagonal numbers, P(j) and P(k), for which their sum
     * and difference are pentagonal and D = |P(k) − P(j)| is minimised;
     * what is the value of D?
     *
     */

    size_t result = (size_t)-1;

    for(size_t j = 1; j < 3000; ++j)
    {
        for(size_t k = j + 1; k < 3000; ++k)
        {
            size_t pents_diff = ((3 * (pow(k,2) - pow(j,2))) - k + j)/2;
            if ( ! pents_.is_pentagonal(pents_diff) )
            {
                continue;
            }
            size_t pents_sum = ((3 * (pow(j,2) + pow(k,2))) - j - k)/2;
            if ( ! pents_.is_pentagonal(pents_sum) )
            {
                continue;
            }
            std::cout << "P(" << j << ")"
                      << ", and P(" << k << ")"
                      << ", sum: " << pents_sum
                      << ", diff: " << pents_diff
                      << std::endl;

            if ( pents_diff < result )
            {
                result = pents_diff;
            }
        }
    }

    std::cout << "PE44 " << result << std::endl;
}
