/*
 * gint.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "gint.hpp"

#include <iostream>
#include <boost/foreach.hpp>

gint::gint() :
    n_()
{}

gint::gint(size_t n) :
    n_()
{
    while(n>0)
    {
        n_.push_front(n%10);
        n /= 10;
    }
}

gint::~gint()
{
}

void gint::print()
{
    BOOST_FOREACH(const short digit, n_)
    {
        std::cout << digit;
    }
    std::cout << std::endl;
}

