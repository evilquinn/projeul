/*
 * pe60.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe60.hpp"
#include <iostream>
#include <fstream>
#include <utils.hpp>
#include <gint.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

std::string& pe60::name()
{
    return name_;
}

void pe60::run()
{
    /*
     * The primes 3, 7, 109, and 673, are quite remarkable. By taking any two
     * primes and concatenating them in any order the result will always be
     * prime. For example, taking 7 and 109, both 7109 and 1097 are prime.
     * The sum of these four primes, 792, represents the lowest sum for a
     * set of four primes with this property.
     *
     * Find the lowest sum for a set of five primes for which any two primes
     * concatenate to produce another prime.
     *
     *
     */

    size_t result = 0;

    size_t base_set[] = { 3, 7, 109, 673 };

    size_t limit = (size_t)-1;

    for ( size_t i = primes_.next_prime(1);
          i < limit;
          i = primes_.next_prime(i) )
    {
        bool next_i = false;
        size_t base_size = sizeof(base_set) / sizeof(size_t);
        for ( size_t j = 0; j < base_size; ++j )
        {
            //std::cout << "checking " << base_set[j] << i << " and " << i << base_set[j] << std::endl;
            if ( ! is_prime(primes_, concat(base_set[j], i)) ||
                 ! is_prime(primes_, concat(i, base_set[j])) )
            {
                next_i = true;
                break;
            }
            if ( j == base_size - 1 )
            {
                // win!
                result = i;
                break;
            }
        }
        if ( next_i )
        {
            continue;
        }
        break;
    }

    std::cout << "result: " << result << std::endl;
}

