/*
 * pe53.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe53.hpp"
#include <iostream>
#include "utils.hpp"

size_t n_c_r(size_t n, size_t r);


std::string& pe53::name()
{
    return name_;
}

void pe53::run()
{
    /*
     *
     * There are exactly ten ways of selecting three from five, 12345:
     *
     * 123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
     *
     * In combinatorics, we use the notation, 5C3 = 10.
     *
     * In general,
     *   nCr = ( n! ) / ( r! * (n−r)! )
     * where
     *   r ≤ n, n! = n * (n−1) * ... * 3 * 2 * 1, and 0! = 1.
     *
     * It is not until n = 23, that a value exceeds one-million:
     *    23C10 = 1144066.
     *
     * How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100,
     * are greater than one-million?
     *
     */

    size_t result = 0;
    std::cout << "result : " << result << std::endl;
}



size_t n_c_r(size_t n, size_t r)
{

}
