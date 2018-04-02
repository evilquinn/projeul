/*
 * pe48.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe48.hpp"
#include <ctype.h>
#include <stdio.h>
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

#define PE48_NUM_DIGITS 10

std::string& pe48::name() { return name_; }
void         pe48::run()
{
    /*
     * The series:
     *
     *     1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317
     *
     * Find the last ten digits of the series:
     *
     *     1^1 + 2^2 + 3^3 + ... + 1000^1000
     */

    int digit_array[PE48_NUM_DIGITS] = { 0 };
    for ( size_t i = 1; i <= 1000; ++i )
    {
        // i*i = i + i + i + ... + i ( i times )
        // i^i = i * i * i * ... * i ( i times )
        //
        // work out i * i
        int mult_digit_array[PE48_NUM_DIGITS] = { 0 };
        mult_digit_array[PE48_NUM_DIGITS - 1] = 1;
        for ( size_t k = 0; k < i; ++k )
        {
            mult_digit_array_by( mult_digit_array, PE48_NUM_DIGITS, i );
        }
        // then add that to term
        add_digit_arrays(
            digit_array, PE48_NUM_DIGITS, mult_digit_array, PE48_NUM_DIGITS );
    }

    std::cout << name() << " " << std::endl;

    for ( size_t i = 0; i < PE48_NUM_DIGITS; ++i )
    {
        std::cout << digit_array[i];
    }

    std::cout << std::endl;
}
