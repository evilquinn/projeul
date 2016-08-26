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
{
    n_.push_front(0);
}

gint::gint(size_t n) :
    n_()
{
    while(n>0)
    {
        n_.push_front(n%10);
        n /= 10;
    }
}

gint::gint(const gint& rhs) :
    n_(rhs.n_)
{
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

gint& gint::operator += (const gint& rhs)
{
    return add(rhs);
}

bool gint::less_than_xor_equal(const gint& rhs, bool equal) const
{
    size_t my_size = n_.size();
    size_t their_size = rhs.n_.size();
    if ( my_size < their_size )
    {
        return !equal;
    }
    if ( my_size > their_size )
    {
        return false;
    }

    for ( size_t i = 0; i < my_size; ++i )
    {
        if ( n_[i] < rhs.n_[i] )
        {
            return !equal;
        }
        if ( n_[i] > rhs.n_[i] )
        {
            return false;
        }
    }

    return equal;
}

gint& gint::operator++()
{
    size_t end = n_.size() - 1;
    return add_digit_at_pos(end, 1);
}

gint gint::operator++(int)
{
    gint tmp(*this);
    operator++();
    return tmp;
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

    size_t carry_on_pos = pos;
    while(n_[carry_on_pos] >= 10)
    {
        n_[carry_on_pos] -= 10;
        if(--carry_on_pos < pos)
        {
            ++(n_[carry_on_pos]);
        }
        else
        {
            n_.push_front(1);
            ++pos;
            break;
        }
    }
    return *this;
}


gint& gint::subtract_digit_at_pos(size_t& pos, uint8_t digit)
{
    if ( digit > 9 )
    {
        throw std::invalid_argument("digit arguement isn't a single digit");
    }
    if ( pos >= n_.size() )
    {
        throw std::invalid_argument("pos argument greater than number size");
    }
    if ( n_.size() == 1 && n_[0] <= digit )
    {
        n_.clear();
        n_.push_front(0);
        return *this;
    }

    while ( pos < n_.size() )
    {
        uint8_t borrowed = 0;
        if ( n_[pos] < digit )
        {
            n_[pos] += 10;
            ++borrowed;
        }
        n_[pos] -= digit;
        digit = borrowed;
        --pos;
    }

    while ( n_.size() > 1 && n_[0] == 0 )
    {
        n_.pop_front();
    }
    return *this;
}

gint& gint::add_reverse_of(const gint rhs)
{
    // already took a copy, safe in case this == &rhs
    // (which it probably will be in my use case)
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

gint& gint::multiply_by_by_adding(size_t mult_by)
{
    gint add_to;

    for(size_t i = 0; i < mult_by; ++i)
    {
        add_to.add(*this);
    }

    *this = add_to;

    return *this;
}

gint& gint::multiply_by(size_t mult_by)
{
    if ( mult_by == 0 )
    {
        n_.clear();
        n_.push_front(0);
        return *this;
    }

    size_t pow_ten = 0;
    size_t limit = mult_by;
    gint result;

    while ( mult_by <= limit && mult_by > 0 )
    {
        uint8_t mult_digit = mult_by % 10;
        gint interim(*this);
        if ( mult_digit != 0 )
        {
            interim.multiply_by_digit(mult_digit);
        }

        for ( size_t i = 0; i < pow_ten; ++i )
        {
            interim.n_.push_back(0);
        }
        result.add(interim);
        ++pow_ten;
        mult_by /= 10;
    }

    *this = result;

    return *this;
}

gint& gint::multiply_by_digit(uint8_t digit)
{
    if ( digit > 9 )
    {
        throw std::invalid_argument("digit arguement isn't a single digit");
    }


    size_t start = n_.size() - 1;
    size_t pos = start;
    size_t carry_on = 0;
    while( pos < n_.size() )
    {
        n_[pos] *= digit;
        n_[pos] += carry_on;
        if ( n_[pos] > 9 )
        {
            carry_on = n_[pos] / 10;
            n_[pos] %= 10;
        }
        else
        {
            carry_on = 0;
        }

        --pos;
    }

    while ( carry_on > 0 )
    {
        n_.push_front(carry_on % 10);
        carry_on /= 10;
    }

    return *this;
}

size_t gint::sum_digits()
{
    size_t result = 0;
    BOOST_FOREACH ( const uint8_t digit, n_ )
    {
        result += digit;
    }
    return result;
}


