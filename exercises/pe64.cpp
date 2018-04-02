/*
 * pe64.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe64.hpp"
#include <cmath>
#include <iostream>

std::string& pe64::name() { return name_; }
void         pe64::run()
{
    /*
     * ffs
     * https://projecteuler.net/problem=64
     *
     */

    size_t odd_period_count = 0;
    for ( size_t i = 2; i <= 10000; ++i )
    {
        size_t m                = sqrt( i );
        size_t digit            = m;
        size_t denom_part       = 1;
        size_t numer_part       = 0;
        size_t first_denom_part = 0;
        size_t first_numer_part = 0;
        size_t msq              = m * m;
        if ( i == msq )
        {
            //    std::cout << "iter 0"
            //              << " : V" << i
            //              << " = " << m
            //              << "\n" << std::endl;
            continue;
        }
        size_t period = 0;

        while ( true )
        {
            //    std::cout << "iter " << period
            //              << " : V" << i << " + " << numer_part
            //              << " / " << denom_part
            //              << " = " << digit << std::endl;
            numer_part = ( denom_part * digit ) - numer_part;
            denom_part = ( i - ( numer_part * numer_part ) ) / denom_part;
            if ( first_denom_part == 0 )
            {
                first_denom_part = denom_part;
                first_numer_part = numer_part;
            }
            else if ( denom_part == first_denom_part &&
                      numer_part == first_numer_part )
            {
                // back at the start!
                break;
            }
            digit = ( m + numer_part ) / denom_part;
            ++period;
        }

        if ( ( period & 1 ) != 0u )
        {
            ++odd_period_count;
        }

        // std::cout << std::endl;
    }

    std::cout << name() << ": " << odd_period_count << std::endl;
}
