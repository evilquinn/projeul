/*
 * pe57.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe57.hpp"
#include <gint.hpp>
#include <iostream>
#include <utils.hpp>

std::string& pe57::name() { return name_; }
void         pe57::run()
{
    /*
     *
     * It is possible to show that the square root of two can be expressed as
     * an infinite continued fraction:
     *
     *   √ 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...
     *
     * By expanding this for the first four iterations, we get:
     *
     * 1 + 1/2 = 3/2 = 1.5
     * 1 + 1/(2 + 1/2) = 7/5 = 1.4
     * 1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
     * 1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
     *
     * The next three expansions are 99/70, 239/169, and 577/408, but the
     * eighth expansion, 1393/985, is the first example where the number of
     * digits in the numerator exceeds the number of digits in the denominator.
     *
     * In the first one-thousand expansions, how many fractions contain a
     * numerator with more digits than denominator?
     *
     */

    size_t result      = 0;
    gint   numerator   = 1;
    gint   denominator = 1;
    gint   next_denominator;

    for ( size_t i = 1; i < 1000; ++i )
    {
        next_denominator = numerator + denominator;
        numerator        = next_denominator + denominator;
        denominator      = next_denominator;
        if ( numerator.num_digits() > denominator.num_digits() )
        {
            ++result;
        }
    }

    std::cout << "result : " << result << std::endl;
}
