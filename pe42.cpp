/*
 * pe42.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe42.hpp"
#include <ctype.h>
#include <stdio.h>
#include <boost/foreach.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

size_t word_value_alpha_pos( const char* word );

std::string& pe42::name() { return name_; }
void         pe42::run()
{
    /*
     * The nth term of the sequence of triangle numbers is given by,
     * t(n) = ½n(n+1); so the first ten triangle numbers are:
     *
     *     1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
     *
     * By converting each letter in a word to a number corresponding to its
     * alphabetical position and adding these values we form a word value.
     * For example, the word value for SKY is 19 + 11 + 25 = 55 = t10.
     * If the word value is a triangle number then we shall call the word a
     * triangle word.
     *
     * Using ./data/pe42_words.txt, a 16K text file containing nearly
     * two-thousand common English words, how many are triangle words?
     *
     */
    triangle_numbers tris_( 1000 );
    const char*      words[] = {
// pe42_words.txt is already formatted like an initialiser list,
// just get the preprocessor to include the file
#include "data/pe42_words.txt"
    };
    const size_t num_words = 1786;  // I counted the words in the file

    size_t result = 0;
    for ( size_t i = 0; i < num_words; ++i )
    {
        if ( tris_.is_triangle( word_value_alpha_pos( words[i] ) ) )
        {
            ++result;
        }
    }

    std::cout << name() << " " << result << std::endl;
}

size_t word_value_alpha_pos( const char* word )
{
    size_t result      = 0;
    size_t word_length = strlen( word );

    for ( size_t i = 0; i < word_length; ++i )
    {
        // subtract '@ from uppercase letter to get aplhabet position
        result += toupper( word[i] ) - '@';
    }

    return result;
}
