/*
 * pe32.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe32.hpp"
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>

typedef std::map<size_t, bool> digit_map;
bool is_pandigital_for_range( size_t start,
                              size_t end,
                              size_t* ints,
                              size_t ints_size );
bool spy_the_digits( size_t min,
                     size_t max,
                     size_t n,
                     digit_map& reqd_digits );
size_t len_n( size_t n );

std::string& pe32::name() { return name_; }
void pe32::run()
{
    /*
     *
     *
     *
     * We shall say that an n-digit number is pandigital if it makes use of
     * all the digits 1 to n exactly once; for example, the 5-digit number,
     * 15234, is 1 through 5 pandigital.
     *
     * The product 7254 is unusual, as the identity, 39 × 186 = 7254,
     * containing multiplicand, multiplier, and product is 1 through 9
     * pandigital.
     *
     * Find the sum of all products whose multiplicand/multiplier/product
     * identity can be written as a 1 through 9 pandigital.
     * HINT: Some products can be obtained in more than one way so be sure
     * to only include it once in your sum.
     *
     *
     */
    size_t total = 0;
    std::set<size_t> ok_prods;
    for ( size_t mand = 1; mand < 10000; ++mand )
    {
        for ( size_t mier = 1; mier < 10000; ++mier )
        {
            size_t prod     = mand * mier;
            size_t nums[]   = { mand, mier, prod };
            size_t full_len = len_n( mand );
            full_len += len_n( mier );
            full_len += len_n( prod );
            if ( full_len != 9 )
            {
                continue;
            }
            if ( is_pandigital_for_range( 1, 9, nums, 3 ) )
            {
                ok_prods.insert( prod );
            }
        }
    }

    // sum the prods
    BOOST_FOREACH ( size_t prod, ok_prods )
    {
        total += prod;
    }

    std::cout << name() << ": " << total << std::endl;
}

bool is_pandigital_for_range( size_t start,
                              size_t end,
                              size_t* ints,
                              size_t ints_size )
{
    digit_map reqd_digits;
    // do we add or subtract from start to reach end?
    bool forwards = end >= start;
    for ( size_t i = start; forwards ? i <= end : i >= end;
          forwards ? ++i : --i )
    {
        reqd_digits[i] = false;
    }

    for ( size_t i = 0; i < ints_size; ++i )
    {
        bool keep_going = spy_the_digits( forwards ? start : end,
                                          forwards ? end : start,
                                          ints[i],
                                          reqd_digits );
        if ( !keep_going )
        {
            return false;
        }
    }

    // collected data, now check if we got all required digits
    BOOST_FOREACH ( digit_map::value_type i, reqd_digits )
    {
        if ( !i.second )
        {
            return false;
        }
    }

    // we did!
    std::cout << "([" << start << ".." << end << "], ";
    for ( size_t i = 0; i < ints_size; ++i )
    {
        std::cout << ints[i] << ",";
    }
    std::cout << ") is PD!" << std::endl;
    return true;
}

bool spy_the_digits( size_t min,
                     size_t max,
                     size_t n,
                     digit_map& reqd_digits )
{
    size_t left = n;
    while ( left > 0 )
    {
        size_t mod = left % 10;
        if ( mod < min || mod > max )
        {
            // a digit outside the required range
            return false;
        }
        if ( reqd_digits[mod] )
        {
            // we've already seen this number, eeek!
            return false;
        }
        reqd_digits[mod] = true;
        left /= 10;
    }

    return true;
}

size_t len_n( size_t n )
{
    size_t len = 1;
    while ( n > 9 )
    {
        ++len;
        n /= 10;
    }
    return len;
}
