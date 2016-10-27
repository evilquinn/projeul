/*
 * pe65.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe65.hpp"
#include <iostream>
#include <cmath>
#include <gint.hpp>

std::string& pe65::name()
{
    return name_;
}

void pe65::run()
{
    /*
     * ffs
     * https://projecteuler.net/problem=65
     *
     */

    std::cout << "[2; ";

    for ( size_t i = 0; i < 50; ++i )
    {
    }

    std::cout << std::endl;

    size_t digit = 1;
    gint old_denom = 2;
    gint denom = digit;
    size_t three_cycle = 0;
    size_t cycle_n = 1;
    for ( size_t i = 0; i < 100; ++i )
    {
        digit = i == 0 ? 2 : ( three_cycle == 1 ? 2 * cycle_n++ : 1 );
    //    std::cout << digit << ", ";
        if ( i != 0 )
        {
            three_cycle = three_cycle == 2 ? 0 : three_cycle + 1;
        }

        std::cout << denom << ", ";
        gint next_denom = ( denom * digit ) + old_denom;
        old_denom = denom;
        denom = next_denom;
    }

    size_t odd_period_count = 0;
    for ( size_t i = 2; i <= 10000; ++i )
    {
        size_t m = sqrt(i);
        size_t digit = m;
        size_t denom_part = 1;
        size_t numer_part = 0;
        size_t first_denom_part = 0;
        size_t first_numer_part = 0;
        size_t msq = m * m;
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

        if ( period & 1 )
        {
            ++odd_period_count;
        }

        // std::cout << std::endl;
    }
}
