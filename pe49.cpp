/*
 * pe49.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe49.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>

#define PE49_NUM_DIGITS 10


std::string& pe49::name()
{
    return name_;
}

void pe49::run()
{
    /*
     *
     * The arithmetic sequence, 1487, 4817, 8147, in which each of the terms
     * increases by 3330, is unusual in two ways:
     *   (i) each of the three terms are prime, and,
     *   (ii) each of the 4-digit numbers are permutations of one another.
     *
     * There are no arithmetic sequences made up of three 1-, 2-, or 3-digit
     * primes, exhibiting this property, but there is one other 4-digit
     * increasing sequence.
     *
     * What 12-digit number do you form by concatenating the three terms in
     * this sequence?
     *
     */

    std::cout << "PE49 " << std::endl;
}

