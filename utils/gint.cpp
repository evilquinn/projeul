/*
 * gint.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "gint.hpp"

#include <iostream>
#include <stdexcept>
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

gint& gint::add(const gint& rhs)
{
    if ( this == &rhs )
    {
        return add_self(rhs);
    }

    size_t add_to_pos = n_.size() - 1;

    gint_digits_t::const_reverse_iterator digit_to_add = rhs.n_.crbegin();
    while ( digit_to_add != rhs.n_.crend() )
    {
        if(add_to_pos < n_.size())
        {
            add_digit_at_pos(add_to_pos, *digit_to_add);
            --add_to_pos;
        }
        else
        {
            n_.push_front(*digit_to_add);
        }
        ++digit_to_add;
    }

    return *this;
}

gint& gint::add_self(const gint rhs)
{
    // this function took a copy of whatever was passed in, so it's safe
    // to just do the add
    return add(rhs);
}

gint& gint::add(size_t rhs)
{
    size_t add_to_pos = n_.size() - 1;
    while(rhs>0)
    {
        if(add_to_pos < n_.size())
        {
            uint8_t digit_to_add = rhs % 10;
            add_digit_at_pos(add_to_pos, digit_to_add);
            --add_to_pos;
        }
        else
        {
            n_.push_front(rhs % 10);
        }

        rhs /= 10;
    }

    return *this;
}


gint& gint::add_digit_at_pos(size_t& pos, uint8_t digit)
{
    if ( digit > 9 )
    {
        throw std::invalid_argument("digit arguement isn't a single digit");
    }
    if ( pos >= n_.size() )
    {
        throw std::invalid_argument("pos argument greater than number size");
    }

    n_[pos] += digit;

    int carry_on_pos = pos;
    while(n_[carry_on_pos] >= 10)
    {
        n_[carry_on_pos] -= 10;
        if(--carry_on_pos >= 0)
        {
            ++n_[carry_on_pos];
        }
        else
        {
            n_.push_front(1);
            ++pos;
        }
    }
    return *this;
}

gint& gint::add_reverse_of(const gint rhs)
{
    // already took a copy, safe in case this == &rhs
    // consider: making a copy and non-copy variant
    size_t add_to_pos = n_.size() - 1;

    gint_digits_t::const_iterator digit_to_add = rhs.n_.cbegin();
    while ( digit_to_add != rhs.n_.cend() )
    {
        if(add_to_pos < n_.size())
        {
            add_digit_at_pos(add_to_pos, *digit_to_add);
            --add_to_pos;
        }
        else
        {
            n_.push_front(*digit_to_add);
        }
        ++digit_to_add;
    }

    return *this;
}

bool gint::is_palindrome()
{
    size_t front = 0;
    size_t back = n_.size() - 1;
    while ( front < back )
    {
        if ( n_[front] != n_[back] )
        {
            return false;
        }
        ++front;
        --back;
    }
    return true;
}

void gint::print()
{
    BOOST_FOREACH(const short digit, n_)
    {
        std::cout << digit;
    }
    std::cout << std::endl;
}

