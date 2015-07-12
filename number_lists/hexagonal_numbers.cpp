/*
 * hexagonal_numbers.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "hexagonal_numbers.hpp"

#include <string.h>
#include <iostream>
#include <algorithm>

hexagonal_numbers::hexagonal_numbers(size_t num) :
    num_(num),
    hexagonals_(num_ + 1),
    max_()
{
    std::cout << "Calc'ing the first " << num_ << " hexagonal numbers ... ";

    calc_hexagonal_numbers();
    max_ = hexagonals_[num_];

    std::cout << "Done." << std::endl;
}

hexagonal_numbers::~hexagonal_numbers()
{
}

void hexagonal_numbers::calc_hexagonal_numbers()
{
    for(size_t i = 1; i <= num_; ++i)
    {
        hexagonals_[i] = calc_hexagonal_number_for_term(i);
    }
}

void hexagonal_numbers::print()
{
    for ( std::vector<size_t>::iterator i = hexagonals_.begin();
          i != hexagonals_.end();
          ++i)
    {
        std::cout << *i << std::endl;
    }
}

size_t hexagonal_numbers::calc_hexagonal_number_for_term(size_t n)
{
    return n * ((2 * n) - 1 );
}

bool hexagonal_numbers::is_hexagonal(size_t n)
{
//    if ( n >= max_ )
//    {
//        std::cout << n << " largeqr than max " << max_ << std::endl;
//        return false;
//    }
    return std::binary_search(hexagonals_.begin(), hexagonals_.end(), n);
}

size_t hexagonal_numbers::get_term(size_t n)
{
//    if ( n >= num_ )
//    {
//        std::cout << "too high term: " << n << std::endl;
//        return 0;
//    }
    return hexagonals_[n];
}
