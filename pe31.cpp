/*
 * pe31.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe31.hpp"
#include <iostream>
#include <cmath>
#include <set>

std::string& pe31::name()
{
    return name_;
}

void pe31::run()
{
    /*
     *
     * In England the currency is made up of pound, £, and pence, p, and
     * there are eight coins in general circulation:
     *
     *     1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
     *
     * It is possible to make £2 in the following way:
     *
     *     1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
     *
     * How many different ways can £2 be made using any number of coins?
     *
     */

    int result = 0;
    std::cout << "PE31: " << result << std::endl;
}
