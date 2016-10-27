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

    size_t three_cycle = 0;
    size_t cycle_n = 1;
    std::cout << "[2; ";

    for ( size_t i = 0; i < 50; ++i )
    {
        std::cout << ( three_cycle == 1 ? 2 * cycle_n++ : 1 ) << ", ";
        three_cycle = three_cycle == 2 ? 0 : three_cycle + 1;
    }

    std::cout << std::endl;

    const size_t DIGIT = 2;
    gint old_denom = 1;
    gint denom = DIGIT;
    for ( size_t i = 0; i < 100; ++i )
    {
        std::cout << denom << ", ";
        gint next_denom = ( denom * DIGIT ) + old_denom;
        old_denom = denom;
        denom = next_denom;
    }

}
