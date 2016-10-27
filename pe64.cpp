/*
 * pe64.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe64.hpp"
#include <iostream>
#include <cmath>

std::string& pe64::name()
{
    return name_;
}

void pe64::run()
{
    /*
     * ffs
     * https://projecteuler.net/problem=64
     *
     */

    size_t result = 0;

    for ( size_t i = 2; i <= 14; ++i )
    {
        size_t m = sqrt(i);
        size_t digit = m;
        size_t denom_part = 1;
        size_t numer_part = 0;
        size_t msq = m * m;
        if ( i == msq )
        {
            std::cout << "iter 0"
                      << " : V" << i
                      << " = " << m
                      << "\n" << std::endl;
            continue;
        }
        for ( size_t iter = 0; iter < 20; ++iter )
        {
            std::cout << "iter " << iter
                      << " : V" << i << " + " << numer_part
                      << " / " << denom_part
                      << " = " << digit << std::endl;
            numer_part = ( denom_part * digit ) - numer_part;
            denom_part = ( i - ( numer_part * numer_part ) ) / denom_part;
            digit = ( m + numer_part ) / denom_part;
        }

        std::cout << std::endl;
    }

    std::cout << "result: " << result << std::endl;

}
