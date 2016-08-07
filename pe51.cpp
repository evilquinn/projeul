/*
 * pe51.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe51.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <deque>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>


std::string& pe51::name()
{
    return name_;
}

void pe51::run()
{
    /*
     *
     * By replacing the 1st digit of the 2-digit number *3, it turns out that
     * six of the nine possible values:
     *   13, 23, 43, 53, 73, and 83,
     * are all prime.
     *
     * By replacing the 3rd and 4th digits of 56**3 with the same digit, this
     * 5-digit number is the first example having seven primes among the ten
     * generated numbers, yielding the family:
     *   56003, 56113, 56333, 56443, 56663, 56773, and 56993.
     * Consequently 56003, being the first member of this family, is the
     * smallest prime with this property.
     *
     * Find the smallest prime which, by replacing part of the number (not
     * necessarily adjacent digits) with the same digit, is part of an eight
     * prime value family.
     *
     *
     */

    size_t result = 0;

    size_t first = primes_.next_prime(10000);
    bool done = false;

    while ( !done )
    {
        // check is got two zeros
        digit_count_map_t digit_count;
        digit_pattern_map_t digit_pattern;



        first = primes_.next_prime(first);
        if ( ++result > 10 ) done = true;
    }










    std::cout << "result     : " << result << std::endl;
}
