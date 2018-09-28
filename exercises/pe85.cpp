/*
 * pe85.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <iostream>
#include <pe85.hpp>
#include <utils.hpp>

namespace
{  // anonymous

size_t num_rectangles( size_t width, size_t length )
{
    return n_c_r( width + 1, 2 ) * n_c_r( length + 1, 2 );
}

}  // namespace

std::string& pe85::name() { return name_; }
void pe85::run()
{
    size_t guess    = 104;
    size_t target   = 2000000;
    size_t low_diff = -1;
    size_t area     = 0;
    for ( size_t i = 0; i < 3; ++i )
    {
        guess += i;
        for ( size_t j = 2; j < guess / 2; ++j )
        {
            size_t cand = num_rectangles( j, guess - j );
            size_t diff = -1;
            if ( cand < target )
            {
                diff = target - cand;
            }
            else
            {
                diff = cand - target;
            }
            if ( diff < low_diff )
            {
                area     = j * ( guess - j );
                low_diff = diff;
                std::cout << "new low: " << low_diff << ", v: " << cand
                          << std::endl;
            }
        }
    }
    std::cout << "result: " << area << std::endl;
}

/*
 * By counting carefully it can be seen that a rectangular grid measuring
 * 3 by 2 contains eighteen rectangles.
 *
 * Although there exists no rectangular grid that contains exactly two
 * million rectangles, find the area of the grid with the nearest solution.
 *
 */
