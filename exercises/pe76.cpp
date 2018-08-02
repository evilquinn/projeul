/*
 * pe76.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <pe76.hpp>
#include <utils.hpp>

std::string& pe76::name() { return name_; }
void print_terms( std::vector<size_t> terms )
{
    for ( const auto& term : terms )
    {
        std::cout << term << ", ";
    }
    std::cout << "\n";
}

long p_of(long n)
{
    static std::map<long, long> cache { { 0, 1 } };
    long result = 0;
    if ( n < 0 )
    {
        return result;
    }
    if ( cache[n] > 0 )
    {
        return cache[n];
    }

    for ( long k = 1; k <= n; ++k )
    {
         // A little bit of recursion
        long left_n = n - (k * (((3 * k) - 1))) / 2;
        long right_n = n - (k * (((3 * k) + 1))) / 2;

        long left_p = p_of(left_n);
        long right_p = p_of(right_n);

        long sum = left_p + right_p;
        if ( k % 2 == 1 )
        {
            result += sum;
        }
        else
        {
            result -= sum;
        }
    }

    cache[n] = result;
    return result;
}

void pe76::run()
{
    /*
     * It is possible to write five as a sum in exactly six different ways:
     *
     *   4 + 1
     *   3 + 2
     *   3 + 1 + 1
     *   2 + 2 + 1
     *   2 + 1 + 1 + 1
     *   1 + 1 + 1 + 1 + 1
     *
     * How many different ways can one hundred be written as a sum of at
     * least two positive integers?
     *
     *
     */

    long n = 100;
    long result = p_of(n);
    std::cout << --result << std::endl;
}
