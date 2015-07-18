/*
 * pe48.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe48.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>

#define PE48_NUM_DIGITS 10


std::string& pe48::name()
{
    return name_;
}

void pe48::run()
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
    for(size_t i = 1; i <= PE48_NUM_DIGITS; ++i)
    {
        int term_digit_array[PE48_NUM_DIGITS] = { 0 };
        for(size_t j = 0; j < i; ++j)
        {
            add_to_digit_array(term_digit_array, PE48_NUM_DIGITS, i);
        }

        add_digit_arrays(digit_array,      PE48_NUM_DIGITS,
                         term_digit_array, PE48_NUM_DIGITS);
    }


    std::cout << "PE48 " << std::endl;

    for(size_t i = 0; i < PE48_NUM_DIGITS; ++i)
    {
        std::cout << digit_array[i];
    }

    std::cout << std::endl;
}

