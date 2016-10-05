/*
 * pe63.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe63.hpp"
#include <iostream>
#include <cmath>
#include <utils.hpp>
#include <polygonal_numbers.hpp>

std::string& pe63::name()
{
    return name_;
}

void pe63::run()
{
    /*
     * The 5-digit number, 16807=7^5, is also a fifth power. Similarly,
     * the 9-digit number, 134217728=8^9, is a ninth power.
     *
     * How many n-digit positive integers exist which are also an nth power?
     *
     */

    size_t result = 0;

    std::cout << "result: " << result << std::endl;

}
