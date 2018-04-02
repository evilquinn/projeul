/*
 * pe55.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe55.hpp"
#include <gint.hpp>
#include <iostream>
#include <utils.hpp>

bool is_lychrel( size_t i );

std::string& pe55::name() { return name_; }
void         pe55::run()
{
    /*
     *
     * If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
     *
     * Not all numbers produce palindromes so quickly. For example,
     *
     *   349 + 943 = 1292,
     *   1292 + 2921 = 4213
     *   4213 + 3124 = 7337
     *
     * That is, 349 took three iterations to arrive at a palindrome.
     *
     * Although no one has proved it yet, it is thought that some numbers,
     * like 196, never produce a palindrome. A number that never forms a
     * palindrome through the reverse and add process is called a Lychrel
     * number. Due to the theoretical nature of these numbers, and for the
     * purpose of this problem, we shall assume that a number is Lychrel until
     * proven otherwise. In addition you are given that for every number
     * below ten-thousand, it will either (i) become a palindrome in less
     * than fifty iterations, or, (ii) no one, with all the computing power
     * that exists, has managed so far to map it to a palindrome. In fact,
     * 10677 is the first number to be shown to require over fifty iterations
     * before producing a palindrome:
     *
     *   4668731596684224866951378664 (53 iterations, 28-digits).
     *
     * Surprisingly, there are palindromic numbers that are themselves Lychrel
     * numbers; the first example is 4994.
     *
     * How many Lychrel numbers are there below ten-thousand?
     *
     */

    size_t result = 0;

    for ( size_t i = 1; i < 10000; ++i )
    {
        if ( is_lychrel( i ) )
        {
            std::cout << i << std::endl;
            ++result;
        }
    }

    std::cout << name() << ": " << result << std::endl;
}

bool is_lychrel( size_t i )
{
    gint   gi( i );
    size_t iterations = 1;

    while ( iterations < 50 )
    {
        gi.add_reverse_of( gi );
        if ( gi.is_palindrome() )
        {
            break;
        }
        ++iterations;
    }
    return iterations >= 50;
}