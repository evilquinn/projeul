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

    size_t num = 1;

    std::cout << "PE48 " << num << std::endl;
}

