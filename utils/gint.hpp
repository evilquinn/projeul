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
    virtual ~gint();

    gint& add(const gint& rhs);
    gint& add_reverse_of(const gint rhs);
    gint& add(size_t rhs);

    bool is_palindrome();

    void print();

private:
    gint& add_self(const gint rhs);
    gint& add_digit_at_pos(size_t& pos, uint8_t digit);
    typedef std::deque<uint8_t> gint_digits_t;
    gint_digits_t n_;
};

#endif /* GINT_HPP_ */
