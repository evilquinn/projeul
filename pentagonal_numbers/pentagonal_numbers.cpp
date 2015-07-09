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
    pentagonals_()
{
    std::cout << "Calc'ing the first " << num_ << " pentagonal numbers ... ";

    calc_pentagonal_numbers();

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
    return pentagonals_.find(n) != pentagonals_.end();
}

size_t pentagonal_numbers::get_term(size_t n)
{
    std::set<size_t>::iterator it = pentagonals_.begin();

    while ( it != pentagonals_.end() && n > 0 )
    {
        ++it;
        --n;
    }

    if ( it == pentagonals_.end() )
    {
        return 0;
    }

    return *it;
}
