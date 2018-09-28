/*
 * pe39.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe39.hpp"
#include <stdio.h>
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

std::string& pe39::name() { return name_; }
void pe39::run()
{
    /*
     * If p is the perimeter of a right angle triangle with integral length
     * sides, {a,b,c}, there are exactly three solutions for p = 120 :
     *
     *     {20,48,52}, {24,45,51}, {30,40,50}
     *
     * For which value of p ≤ 1000, is the number of solutions maximised?
     *
     */
    int p_with_max_sols = 0;
    int p_max_sols      = 0;
    for ( int p = 0; p <= 1000; ++p )
    {
        int curr_p_max_sols = 0;
        for ( int a = 0; a < p; ++a )
        {
            for ( int b = a; b < p; ++b )
            {
                int c_sqrd = pow( a, 2 ) + pow( b, 2 );
                double c   = sqrt( c_sqrd );
                if ( a + b + c == p )
                {
                    ++curr_p_max_sols;
                }
            }
        }

        if ( curr_p_max_sols > p_max_sols )
        {
            p_max_sols      = curr_p_max_sols;
            p_with_max_sols = p;
        }
    }

    std::cout << name() << " " << p_with_max_sols << std::endl;
}
