/*
 * pe32.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe32.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <boost/foreach.hpp>

typedef std::map<int, bool> digit_map;
bool is_pandigital_for_range(int start, int end, int* ints, int ints_size);
bool spy_the_digits(int min, int max, int n, digit_map& reqd_digits);
int len_n(int min);

std::string& pe32::name()
{
    return name_;
}

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
    int total = 0;
    std::set<int> ok_prods;
    for(int mand = 1; mand < 10000; ++mand)
    {
        for(int mier = 1; mier < 10000; ++mier)
        {
            int prod = mand * mier;
            int nums[] = { mand, mier, prod };
            int full_len = len_n(mand);
            full_len += len_n(mier);
            full_len += len_n(prod);
            if ( full_len != 9 ) { continue; }
            if ( is_pandigital_for_range(1, 9, nums, 3) )
            {
                ok_prods.insert(prod);
            }
        }
    }

    // sum the prods
    BOOST_FOREACH ( int prod, ok_prods )
    {
        total += prod;
    }

    std::cout << "PE32 " << total << std::endl;
}

bool is_pandigital_for_range(int start, int end, int* ints, int ints_size)
{
    digit_map reqd_digits;
    // do we add or subtract from start to reach end?
    bool forwards = end - start >= 0 ? true : false;
    for(int i = start;
        forwards ? i <= end : i >= end;
        forwards ?      ++i :      --i )
    {
        reqd_digits[i] = false;
    }

    bool keep_going = true;
    for(int i = 0; i < ints_size; ++i)
    {
        keep_going = spy_the_digits(forwards ? start : end,
                                    forwards ? end : start,
                                    ints[i],
                                    reqd_digits);
        if ( !keep_going )
        {
            return false;
        }
    }

    // collected data, now check if we got all required digits
    BOOST_FOREACH ( digit_map::value_type i, reqd_digits )
    {
        if ( ! i.second )
        {
            return false;
        }
    }

    // we did!
    std::cout << "([" << start << ".." << end << "], ";
    for(int i=0;i<ints_size;++i)
    {
        std::cout << ints[i] << ",";
    }
    std::cout << ") is PD!" << std::endl;
    return true;
}

bool spy_the_digits(int min, int max, int n, digit_map& reqd_digits)
{
    int left = n;
    while(left>0)
    {
        int mod = left%10;
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
        left/=10;
    }

    return true;
}

int len_n(int n)
{
    int len = 1;
    while(n>9)
    {
        ++len;
        n/=10;
    }
    return len;
}

