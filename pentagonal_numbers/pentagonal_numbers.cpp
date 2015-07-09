/*
 * pentagonal_numbers.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "pentagonal_numbers.hpp"

#include <string.h>
#include <iostream>

pentagonal_numbers::pentagonal_numbers(size_t num) :
    num_(num),
    pentagonals_(),
    max_()
{
    std::cout << "Calc'ing the first " << num_ << " pentagonal numbers ... ";

    calc_pentagonal_numbers();
    max_ = get_term(num_-1);

    std::cout << "Done." << std::endl;
}

pentagonal_numbers::~pentagonal_numbers()
{
}

void pentagonal_numbers::calc_pentagonal_numbers()
{
    for(size_t i = 1; i <= num_; ++i)
    {
        pentagonals_.insert(calc_pentagonal_number_for_term(i));
    }
}

void pentagonal_numbers::print()
{
    for ( std::set<size_t>::iterator i = pentagonals_.begin();
          i != pentagonals_.end();
          ++i)
    {
        std::cout << *i << std::endl;
    }
}

size_t pentagonal_numbers::calc_pentagonal_number_for_term(size_t n)
{
    return n * ( (3 * n) - 1 ) / 2;
}

bool pentagonal_numbers::is_pentagonal(size_t n)
{
//    if ( n >= max_ )
//    {
//        std::cout << n << " largeqr than max " << max_ << std::endl;
//        return false;
//    }
    bool result = pentagonals_.find(n) != pentagonals_.end();
    return result;
}

size_t pentagonal_numbers::get_term(size_t n)
{
//    if ( n >= num_ )
//    {
//        std::cout << "too high term: " << n << std::endl;
//        return 0;
//    }

    std::set<size_t>::iterator it = pentagonals_.begin();
    std::advance(it, n);

    return *it;
}
