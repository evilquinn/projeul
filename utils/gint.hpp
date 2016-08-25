/*
 * gint.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef GINT_HPP_
#define GINT_HPP_

#include <stddef.h>
#include <stdint.h>
#include <deque>

class gint
{
public:
    gint();
    gint(size_t n);
    gint(const gint& rhs);
    virtual ~gint();

    gint& add(const gint& rhs);
    gint& add(size_t rhs);
    gint& multiply_by(size_t rhs);

    // operators
    gint& operator+= (const gint& rhs);
    gint operator+ (const gint& rhs) const;
    bool operator< (const gint& rhs) const;
    bool operator<= (const gint& rhs) const;
    bool operator== (const gint& rhs) const;
    bool operator>= (const gint& rhs) const;
    bool operator> (const gint& rhs) const;


    // utility
    gint& add_reverse_of(const gint rhs);
    size_t sum_digits();
    bool is_palindrome();
    void print();

private:
    bool less_than_or_equal(const gint& rhs, bool or_equal) const;
    gint& add_self(const gint rhs);
    gint& add_digit_at_pos(size_t& pos, uint8_t digit);
    gint& multiply_by_digit(uint8_t digit);
    gint& multiply_by_by_adding(size_t rhs);
    typedef std::deque<uint8_t> gint_digits_t;
    gint_digits_t n_;
};

#endif /* GINT_HPP_ */
