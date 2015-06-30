/*
 * pe40.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe40.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>
#include "utils.hpp"
#include <stdio.h>

int select_digit(int n, int index);

std::string& pe40::name()
{
    return name_;
}

void pe40::run()
{
    /*
     */
    int result = 1;
    int d = 1;
    int n = 1;
    bool done1 = false;
    bool done10 = false;
    bool done100 = false;
    bool done1000 = false;
    bool done10000 = false;
    bool done100000 = false;
    bool done1000000 = false;
    while( !done1 || !done10 || !done100 || !done1000 || !done10000 || !done100000 || !done1000000 )
    {
        if ( !done1 && d >= 1 )
        {
            result *= select_digit(n, d == 1 ? 0 : num_digits(n) - (d-1));
            done1 = true;
        }
        if ( !done10 && d >= 10 )
        {
            result *= select_digit(n, d == 10 ? 0 : num_digits(n) - (d-10));
            done10 = true;
        }
        if ( !done100 && d >= 100 )
        {
            result *= select_digit(n, d == 100 ? 0 : num_digits(n) - (d-100));
            done100 = true;
        }
        if ( !done1000 && d >= 1000 )
        {
            result *= select_digit(n, d == 1000 ? 0 : num_digits(n) - (d-1000));
            done1000 = true;
        }
        if ( !done10000 && d >= 10000 )
        {
            result *= select_digit(n, d == 10000 ? 0 : num_digits(n) - (d-10000));
            done10000 = true;
        }
        if ( !done100000 && d >= 100000 )
        {
            result *= select_digit(n, d == 100000 ? 0 : num_digits(n) - (d-100000));
            done100000 = true;
        }
        if ( !done1000000 && d >= 1000000 )
        {
            result *= select_digit(n, d == 1000000 ? 0 : num_digits(n) - (d-1000000));
            done1000000 = true;
        }

        d += num_digits(n);
        ++n;
    }

    std::cout << "PE40 " << result << std::endl;
}


int select_digit(int n, int index)
{
    int chosen_one = 0;
    int num_digs = num_digits(n);
    if ( index < 0 || index >= num_digs )
    {
        return -1;
    }

    // remember, num_digits is 1-based, index is 0-based
    while(num_digs-1>index)
    {
        // chop
        n/=10;
        --num_digs;
    }

    //capture
    chosen_one = n%10;
    return chosen_one;
}
