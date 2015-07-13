/*
 * pe46.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe46.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>
#include <ctype.h>


std::string& pe46::name()
{
    return name_;
}

void pe46::run()
{
    /*
     *
     *
     * It was proposed by Christian Goldbach that every odd composite number
     * can be written as the sum of a prime and twice a square.
     *
     * 9 = 7 + 2×1^2
     * 15 = 7 + 2×2^2
     * 21 = 3 + 2×3^2
     * 25 = 7 + 2×3^2
     * 27 = 19 + 2×2^2
     * 33 = 31 + 2×1^2
     *
     * It turns out that the conjecture was false.
     *
     * What is the smallest odd composite that cannot be written as the sum of
     * a prime and twice a square?
     *
     */

    size_t result = 0;

    for(size_t i = 1; i <= PE46_NUM_PRIMES; ++i)
    {
        squares_[i] = pow(i, 2);
    }

    for(size_t i = 35; i < 10000; i += 2)
    {
        if ( ! primes_.is_prime(i) )
        {
            if ( ! fulfills_goldbachs_conjecture(i) )
            {
                result = i;
                break;
            }
        }
    }

    std::cout << "PE46 " << result << std::endl;
}


bool pe46::fulfills_goldbachs_conjecture(size_t i)
{
    size_t prev = i;
    do
    {
        prev = prev_prime(prev);
        if ( prev == 2 )
        {
            continue;
        }
        size_t diff = i - prev;
        size_t poss_square = diff / 2;
        if(std::binary_search(squares_.begin(), squares_.end(), poss_square))
        {
            return true;
        }
    }
    while(prev > 2);

    return false;
}

size_t pe46::prev_prime(size_t i)
{
    if ( i < 3 )
    {
        return 2;
    }

    do
    {
        i -= 2;
    }
    while(i > 1 && !primes_.is_prime(i) );
    return i;
}
