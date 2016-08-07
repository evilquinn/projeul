/*
 * pe52.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe52.hpp"
#include <iostream>
#include "utils.hpp"


std::string& pe52::name()
{
    return name_;
}

void pe52::run()
{
    /*
     * It can be seen that the number, 125874, and its double, 251748, contain
     * exactly the same digits, but in a different order.
     *
     * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
     * contain the same digits.
     *
     */

    size_t best_count = 0;
    std::cout << "best count    : " << best_count << std::endl;
}
