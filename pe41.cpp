/*
 * pe41.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe41.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>


std::string& pe41::name()
{
    return name_;
}

void pe41::run()
{
    /*
     * We shall say that an n-digit number is pandigital if it makes use of
     * all the digits 1 to n exactly once. For example, 2143 is a 4-digit
     * pandigital and is also prime.
     *
     * What is the largest n-digit pandigital prime that exists?
     *
     */
    int result = 1;
    std::cout << "PE41 " << result << std::endl;
}
