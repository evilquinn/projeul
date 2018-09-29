/*
 * pe36.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe36.hpp"
#include <boost/foreach.hpp>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

char* conv_to_bin( char* dest, int max, long long unsigned n );
bool is_palendrome( const char* in );

std::string& pe36::name() { return name_; }
void pe36::run()
{
    /*
     *
     * The decimal number 585 = 1001001001(base2) (binary), is palindromic in
     * both bases.
     *
     * Find the sum of all numbers, less than one million, which are
     * palindromic in base 10 and base 2.
     *
     * (Please note that the palindromic number, in either base, may not
     *  include leading zeros.)
     *
     */

    long long unsigned limit = 1000000;
    long long unsigned sum   = 0;

    for ( unsigned long long i = 1; i < limit; ++i )
    {
        int lim_str_size = num_digits( limit ) + 1;
        char lim_str[lim_str_size];
        snprintf( lim_str, lim_str_size, "%llu", i );
        int bin_str_size = 30;
        char bin_str[bin_str_size];
        memset( bin_str, 0, bin_str_size );
        char* bin_begin = conv_to_bin( bin_str, bin_str_size, i );
        if ( is_palendrome( bin_begin ) && is_palendrome( lim_str ) )
        {
            sum += i;
            std::cout << lim_str << " and " << bin_begin << " win"
                      << std::endl;
        }
    }

    std::cout << name() << " " << sum << std::endl;
}

char* conv_to_bin( char* dest, int max, long long unsigned n )
{
    // null terminate first!
    int w_pos   = max - 1;
    dest[w_pos] = 0;
    while ( n > 0 )
    {
        dest[--w_pos] = n % 2 + '0';
        n /= 2;
    }

    return dest + w_pos;
}

bool is_palendrome( const char* in )
{
    int size  = strlen( in );
    int range = size / 2;
    int i     = 0;
    int j     = size - 1;
    for ( ; i < range; )
    {
        if ( in[i] != in[j] )
        {
            return false;
        }
        ++i;
        --j;
    }
    return true;
}
