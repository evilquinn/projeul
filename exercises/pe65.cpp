/*
 * pe65.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe65.hpp"
#include <cmath>
#include <gint.hpp>
#include <iostream>

std::string& pe65::name() { return name_; }
void pe65::run()
{
    /*
     * ffs
     * https://projecteuler.net/problem=65
     *
     */

    size_t result     = 0;
    gint e_combo[101] = { gint( 0 ) };

    size_t three_cycle = 0;
    size_t cycle_n     = 1;
    for ( auto& i : e_combo )
    {
        gint digit( three_cycle == 1 ? 2 * cycle_n++ : 1 );
        i           = gint( digit );
        three_cycle = ( three_cycle == 2 ? 0 : three_cycle + 1 );
    }

    gint old_denom( 1 );
    gint denom( e_combo[0] );
    gint old_numer( 1 );
    gint numer( 2 );
    for ( size_t i = 0; i < 100; ++i )
    {
        if ( i == 99 )
        {
            result = numer.sum_digits();
            break;
        }
        gint next_numer = ( numer * e_combo[i] ) + old_numer;
        old_numer       = numer;
        numer           = next_numer;

        gint next_denom = ( denom * e_combo[i + 1] ) + old_denom;
        old_denom       = denom;
        denom           = next_denom;
    }

    std::cout << name() << ": " << result << std::endl;
}
