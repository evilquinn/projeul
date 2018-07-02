/*
 * pe74.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe74.hpp>
#include <iostream>
#include <map>
#include <utils.hpp>
#include <boost/multiprecision/cpp_int.hpp>

std::string& pe74::name() { return name_; }

boost::multiprecision::cpp_int sum_factorial_of_digits_of(boost::multiprecision::cpp_int n)
{
    boost::multiprecision::cpp_int result = 0;
    while ( n > 0 )
    {
        boost::multiprecision::cpp_int d = n % 10;
        boost::multiprecision::cpp_int dfac = 1;
        for ( ; d > 1; --d )
        {
            dfac *= d;
        }
        result += dfac;
        n /= 10;
    }

    return result;
}

void         pe74::run()
{
    /*
     * The number 145 is well known for the property that the sum of the
     * factorial of its digits is equal to 145:
     *
     *     1! + 4! + 5! = 1 + 24 + 120 = 145
     *
     * Perhaps less well known is 169, in that it produces the longest chain
     * of numbers that link back to 169; it turns out that there are only
     * three such loops that exist:
     *
     *     169 → 363601 → 1454 → 169
     *     871 → 45361 → 871
     *     872 → 45362 → 872
     *
     * It is not difficult to prove that EVERY starting number will
     * eventually get stuck in a loop. For example,
     *
     *     69 → 363600 → 1454 → 169 → 363601 (→ 1454)
     *     78 → 45360 → 871 → 45361 (→ 871)
     *     540 → 145 (→ 145)
     *
     * Starting with 69 produces a chain of five non-repeating terms, but
     * the longest non-repeating chain with a starting number below one
     * million is sixty terms.
     *
     * How many chains, with a starting number below one million, contain
     * exactly sixty non-repeating terms?
     *
     */

    size_t result = 0;

    size_t limit3 = 1000000;
    size_t i = 1000;
    while ( i < limit3 )
    {
        auto attempt = sum_factorial_of_digits_of(i);
        if ( attempt == 367945 || attempt == 367954 )
        {
            // any number which results in either of those two sums of factorial
            // of digits will result in a 60-length chain, nice!
            ++result;
        }
        ++i;
    }
    std::cout << result << std::endl;

}
