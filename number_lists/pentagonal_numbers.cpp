/*
 * pentagonal_numbers.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "pentagonal_numbers.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

pentagonal_numbers::pentagonal_numbers( size_t num )
    : num_( num ), pentagonals_( num_ + 1 ), max_()
{
    std::cout << "Calc'ing the first " << num_ << " pentagonal numbers ... ";

    calc_pentagonal_numbers();
    max_ = pentagonals_[num_];

    std::cout << "Done." << std::endl;
}

pentagonal_numbers::~pentagonal_numbers() = default;
void pentagonal_numbers::calc_pentagonal_numbers()
{
    for ( size_t i = 1; i <= num_; ++i )
    {
        pentagonals_[i] = calc_pentagonal_number_for_term( i );
    }
}

void pentagonal_numbers::print()
{
    for ( unsigned long& pentagonal : pentagonals_ )
    {
        std::cout << pentagonal << std::endl;
    }
}

size_t pentagonal_numbers::calc_pentagonal_number_for_term( size_t n )
{
    return n * ( ( 3 * n ) - 1 ) / 2;
}

bool pentagonal_numbers::is_pentagonal( size_t n )
{
    //    if ( n >= max_ )
    //    {
    //        std::cout << n << " largeqr than max " << max_ << std::endl;
    //        return false;
    //    }
    return std::binary_search( pentagonals_.begin(), pentagonals_.end(), n );
}

size_t pentagonal_numbers::get_term( size_t n )
{
    //    if ( n >= num_ )
    //    {
    //        std::cout << "too high term: " << n << std::endl;
    //        return 0;
    //    }
    return pentagonals_[n];
}
