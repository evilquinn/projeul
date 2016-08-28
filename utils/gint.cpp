/*
 * gint.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "gint.hpp"

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <boost/foreach.hpp>

gint::gint() :
    n_(),
    is_negative(false)
{
    n_.push_front(0);
}

gint::gint(size_t n) :
    n_(),
    is_negative(false)
{
    construct_digits_from_positive(n);
}

gint::gint(long int n) :
    n_(),
    is_negative(n<0)
{
    construct_digits_from_positive( n<0 ? -n : n );
}

gint::gint(int n) :
    gint(static_cast<long int>(n))
{}


void gint::construct_digits_from_positive(size_t n)
{
    if ( n == 0 )
    {
        n_.push_front(0);
        return;
    }
    while(n>0)
    {
        n_.push_front(n%10);
        n /= 10;
    }
}


gint::gint(const gint& rhs) :
    n_(rhs.n_),
    is_negative(rhs.is_negative)
{
}

gint::~gint()
{
}

gint& gint::add(const gint& rhs)
{
    if ( rhs.is_negative )
    {
        return subtract(rhs.abs());
    }

    if ( this == &rhs )
    {
        gint rhs_copy(rhs);
        return add(rhs_copy);
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

gint& gint::operator -= (const gint& rhs)
{
    return subtract(rhs);
}

gint& gint::operator *= (const gint& rhs)
{
    return multiply_by(rhs);
}



bool gint::less_than_xor_equal(const gint& rhs, bool equal) const
{
    if ( is_negative )
    {
        if ( !rhs.is_negative )
        {
            return !equal;
        }
        else
        {
            return rhs.abs().less_than_xor_equal(abs(), equal);
        }
    }
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

gint gint::abs() const
{
    gint absolute(*this);
    absolute.is_negative = false;
    return absolute;
}

gint& gint::subtract(const gint& rhs)
{
    if ( rhs.is_negative )
    {
        return add(rhs.abs());
    }

    if ( *this <= rhs )
    {
        gint temp(*this);
        n_ = rhs.n_;
        subtract(temp);
        is_negative = *this != 0;
        return *this;
    }

    // we need to take a copy if we're adding a ref to myself
    if ( this == &rhs )
    {
        gint rhs_copy(rhs);
        return subtract(rhs_copy);
    }

    size_t rhs_pos = rhs.n_.size() - 1;
    size_t my_pos = n_.size() - 1;
    uint8_t part_subtract = 0;
    uint8_t borrowed = 0;
    while ( rhs_pos < rhs.n_.size() || borrowed != 0 )
    {
        part_subtract = borrowed;
        if ( rhs_pos < rhs.n_.size() )
        {
            part_subtract += rhs.n_[rhs_pos];
        }

        borrowed = 0;
        while ( n_[my_pos] < part_subtract )
        {
            ++borrowed;
            n_[my_pos] += 10;
        }

        n_[my_pos] -= part_subtract;
        --rhs_pos;
        --my_pos;
    }

    // truncate leading zeros
    while ( n_.size() > 1 && n_[0] == 0 )
    {
        n_.pop_front();
    }

    return *this;
}


gint& gint::add_reverse_of(const gint& rhs)
{
    // take copy if necessary
    if ( this == &rhs )
    {
        gint rhs_copy(rhs);
        return add_reverse_of(rhs_copy);
    }

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
    if ( is_negative )
    {
        std::cout << '-';
    }
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

gint& gint::multiply_by(const gint& mult_by)
{
    if ( mult_by == 0 )
    {
        *this = mult_by;
        return *this;
    }

    if ( this == &mult_by )
    {
        gint copy(mult_by);
        return multiply_by(copy);
    }

    size_t pow_ten = 0;
    size_t pos = mult_by.n_.size() - 1;
    gint result;

    while ( pos < mult_by.n_.size() )
    {
        uint8_t mult_digit = mult_by.n_[pos];
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
        --pos;
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


