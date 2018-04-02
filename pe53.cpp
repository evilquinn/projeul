/*
 * pe53.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe53.hpp"
#include <iostream>
#include "utils.hpp"

std::string& pe53::name() { return name_; }
void         pe53::run()
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

    for ( size_t n = 23; n <= 100; ++n )
    {
        for ( size_t r = 1; r <= n; ++r )
        {
            size_t ncr = n_c_r( n, r );
            // printf("%zu\t%zu\t%zu\n", ncr, n, r);
            if ( ncr > 1000000 )
            {
                result += ( ( ( n - r ) - r ) + 1 );
                break;
            }
        }
    }
    std::cout << name() << ": " << result << std::endl;
}
