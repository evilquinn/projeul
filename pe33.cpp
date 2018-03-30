/*
 * pe33.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe33.hpp"
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>

std::string& pe33::name() { return name_; }
void         pe33::run()
{
    /*
     * The fraction 49/98 is a curious fraction, as an inexperienced
     * mathematician in attempting to simplify it may incorrectly believe
     * that 49/98 == 4/8, which is correct, is obtained by cancelling the 9s.
     *
     * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
     *
     * There are exactly four non-trivial examples of this type of fraction,
     * less than one in value, and containing two digits in the numerator
     * and denominator.
     *
     * If the product of these four fractions is given in its lowest common
     * terms, find the value of the denominator.
     */

    int denr_prod = 1;
    int numr_prod = 1;
    for ( int numr = 11; numr < 100; ++numr )
    {
        int n_fir_dig = numr / 10;
        int n_sec_dig = numr % 10;
        if ( n_sec_dig == 0 )
        {
            ++n_sec_dig;
            ++numr;
        }

        int denr_lim = ( n_sec_dig + 1 ) * 10;
        for ( int denr = ( n_sec_dig * 10 ) + 1; denr < denr_lim; ++denr )
        {
            int d_sec_dig = denr % 10;
            if ( n_fir_dig / d_sec_dig == 1 )
            {
                continue;
            }
            if ( (double)numr / denr == (double)n_fir_dig / d_sec_dig )
            {
                numr_prod *= n_fir_dig;
                denr_prod *= d_sec_dig;
                std::cout << numr << "/" << denr << " = " << n_fir_dig << "/"
                          << d_sec_dig << std::endl;
            }
        }
    }
    int total = 0;
    std::cout << "PE33 " << numr_prod << "/" << denr_prod << std::endl;
    std::cout << "PE33 " << total << std::endl;
}
