/*
 * pe56.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe56.hpp"
#include <iostream>
#include <utils.hpp>


std::string& pe56::name()
{
    return name_;
}

void pe56::run()
{
    /*
     * A googol (10^100) is a massive number: one followed by one-hundred zeros;
     * 100^100 is almost unimaginably large: one followed by two-hundred zeros.
     * Despite their size, the sum of the digits in each number is only 1.
     *
     * Considering natural numbers of the form, a^b, where a, b < 100, what is
     * the maximum digital sum?
     *
     */

    size_t result = 0;

    std::cout << "result : " << result << std::endl;
}

