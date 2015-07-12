/*
 * triangle_numbers.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "triangle_numbers.hpp"

#include <string.h>
#include <iostream>

triangle_numbers::triangle_numbers(size_t num) :
    num_(num),
    triangles_()
{
    std::cout << "Calc'ing the first " << num_ << " triangle numbers ... ";

    calc_triangle_numbers();

    std::cout << "Done." << std::endl;
}

triangle_numbers::~triangle_numbers()
{
}

void triangle_numbers::calc_triangle_numbers()
{
    for(size_t i = 1; i <= num_; ++i)
    {
        triangles_.insert(calc_triangle_number_for_term(i));
    }
}

void triangle_numbers::print()
{
    for ( std::set<size_t>::iterator i = triangles_.begin();
          i != triangles_.end();
          ++i)
    {
        std::cout << *i << std::endl;
    }
}

size_t triangle_numbers::calc_triangle_number_for_term(size_t n)
{
    return (n+1)*(n/2.0);
}

bool triangle_numbers::is_triangle(size_t n)
{
    return triangles_.find(n) != triangles_.end();
}

size_t triangle_numbers::get_term(size_t n)
{
//    if ( n >= num_ )
//    {
//        std::cout << "too high term: " << n << std::endl;
//        return 0;
//    }

    std::set<size_t>::iterator it = triangles_.begin();
    std::advance(it, n);

    return *it;
}
