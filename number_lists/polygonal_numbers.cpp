/*
 * polygonal_numbers.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "polygonal_numbers.hpp"

#include <string.h>
#include <iostream>
#include <algorithm>

polygonal_numbers::polygonal_numbers(size_t num,
                                     function_of_n func) :
    num_(num),
    number_func_(func),
    numbers_(num_ + 1)
{
    std::cout << "Calc'ing the first "
              << num_
              << " numbers ... "
              << std::endl;

    calc_polygonal_numbers();

    std::cout << "Done." << std::endl;
}

polygonal_numbers::~polygonal_numbers()
{
}

void polygonal_numbers::calc_polygonal_numbers()
{
    for(size_t i = 1; i <= num_; ++i)
    {
        numbers_[i] = number_func_(i);
    }
}

void polygonal_numbers::print()
{
    for ( std::vector<size_t>::iterator i = numbers_.begin();
          i != numbers_.end();
          ++i)
    {
        std::cout << *i << std::endl;
    }
}

size_t polygonal_numbers::triangle(size_t n)
{
    return ( n * ( n + 1 ) ) / 2;
}

size_t polygonal_numbers::square(size_t n)
{
    return n * n;
}

size_t polygonal_numbers::pentagonal(size_t n)
{
    return ( n * ( ( n * 3 ) - 1 ) ) / 2;
}

size_t polygonal_numbers::hexagonal(size_t n)
{
    return n * ( ( n * 2 ) - 1 );
}

size_t polygonal_numbers::heptagonal(size_t n)
{
    return ( n * ( ( n * 5 ) - 3 ) ) / 2;
}

size_t polygonal_numbers::octagonal(size_t n)
{
    return n * ( ( n * 3 ) - 2 );
}

bool polygonal_numbers::is_in(size_t n)
{
    return std::binary_search(numbers_.begin(), numbers_.end(), n);
}

size_t polygonal_numbers::get_term(size_t n)
{
    if ( num_ < n )
    {
        throw std::invalid_argument("n too big");
    }
    return numbers_[n];
}
