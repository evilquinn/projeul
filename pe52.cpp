/*
 * pe52.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe52.hpp"
#include <iostream>
#include "utils.hpp"


size_t pe52_next_number(size_t num);


std::string& pe52::name()
{
    return name_;
}

void pe52::run()
{
    /*
     * It can be seen that the number, 125874, and its double, 251748, contain
     * exactly the same digits, but in a different order.
     *
     * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
     * contain the same digits.
     *
     */

    // it'll almost certainly begin with a 1.

    const size_t begin = 123456;
    const size_t end = begin * 2;
    const size_t iters = 6;
    bool done = false;
    size_t current = begin;
    size_t result = 0;
    while ( !done )
    {
        for(unsigned i = 2; i <= iters; ++i)
        {
            if ( !same_digits(current, current * i) )
            {
                break;
            }
            else
            {
                if ( i == iters )
                {
                    result = current;
                    done = true;
                }
            }

        }

        current = pe52_next_number(current);
        if ( current > end )
        {
            done = true;
        }
    }

    std::cout << "result : " << result << std::endl;
}

size_t pe52_next_number(size_t num)
{
    return num + 1;
}
