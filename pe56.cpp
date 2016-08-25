/*
 * pe56.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe56.hpp"
#include <iostream>
#include <utils.hpp>
#include <gint.hpp>


std::string& pe56::name()
{
    return name_;
}

void pe56::run()
{
    /*
     * A googol (10^100) is a massive number: one followed by one-hundred zeros;
     * 100^100 is almost unimaginably large: one followed by two-hundred zeros.
     * Despite their size, the sum of the digits in each number is only 1.
     *
     * Considering natural numbers of the form, a^b, where a, b < 100, what is
     * the maximum digital sum?
     *
     */

    size_t result = 0;

    for ( size_t a = 99; a > 0; --a )
    {
        gint ga(a);
        for ( size_t b = 0; b < 100; ++b )
        {
            ga.multiply_by(a);
            size_t digit_sum = ga.sum_digits();
            if ( digit_sum > result )
            {
                result = digit_sum;
            }
        }
    }

    std::cout << "result : " << result << std::endl;
}

