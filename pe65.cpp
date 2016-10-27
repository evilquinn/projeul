/*
 * pe65.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe65.hpp"
#include <iostream>
#include <cmath>

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

}
