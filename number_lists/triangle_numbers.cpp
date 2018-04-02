/*
 * triangle_numbers.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "triangle_numbers.hpp"

#include <string.h>
#include <algorithm>
#include <iostream>

triangle_numbers::triangle_numbers( size_t num )
    : num_( num ), triangles_( num_ + 1 )
{
    std::cout << "Calc'ing the first " << num_ << " triangle numbers ... ";

    calc_triangle_numbers();

    std::cout << "Done." << std::endl;
}

triangle_numbers::~triangle_numbers() = default;
void triangle_numbers::calc_triangle_numbers()
{
    for ( size_t i = 1; i <= num_; ++i )
    {
        triangles_[i] = calc_triangle_number_for_term( i );
    }
}

void triangle_numbers::print()
{
    for ( unsigned long& triangle : triangles_ )
    {
        std::cout << triangle << std::endl;
    }
}

size_t triangle_numbers::calc_triangle_number_for_term( size_t n )
{
    return ( n + 1 ) * ( n / 2.0 );
}

bool triangle_numbers::is_triangle( size_t n )
{
    return std::binary_search( triangles_.begin(), triangles_.end(), n );
}

size_t triangle_numbers::get_term( size_t n )
{
    //    if ( n >= num_ )
    //    {
    //        std::cout << "too high term: " << n << std::endl;
    //        return 0;
    //    }
    return triangles_[n];
}
