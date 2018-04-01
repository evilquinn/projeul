/*
 * pe62.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe62.hpp"
#include <cmath>
#include <iostream>
#include <polygonal_numbers.hpp>
#include <utils.hpp>

size_t cube_n( size_t n );

std::string& pe62::name() { return name_; }
void         pe62::run()
{
    /*
     * The cube, 41063625 (345^3), can be permuted to produce two other cubes:
     * 56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the
     * smallest
     * cube which has exactly three permutations of its digits which are also
     * cube.
     *
     * Find the smallest cube for which exactly five permutations of its
     * digits are cube.
     *
     */

    polygonal_numbers cubes( 10000, cube_n );
    size_t            result = 0;

    for ( size_t i = 0; i < 10000; ++i )
    {
        size_t cand        = cubes.get_term( i );
        size_t cand_length = num_digits( cand );
        size_t limit       = pow( 10, cand_length );
        size_t count       = 1;
        // does cand have four other cube permutations?
        size_t perm_cand;
        for ( size_t perm_cand_term = i + 1;
              ( perm_cand = cubes.get_term( perm_cand_term ) ) < limit;
              ++perm_cand_term )
        {
            if ( same_digits( perm_cand, cand ) )
            {
                ++count;
                if ( count == 5 )
                {
                    break;
                }
            }
        }

        if ( count == 5 )
        {
            result = cand;
            break;
        }
    }

    std::cout << "result: " << result << std::endl;
}

size_t cube_n( size_t n ) { return n * n * n; }
