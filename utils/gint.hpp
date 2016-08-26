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
    gint& operator += (const gint& rhs);
    gint& operator++();
    gint operator++(int);

    // utility
    gint& add_reverse_of(const gint rhs);
    size_t sum_digits();
    bool is_palindrome();
    void print();
    bool less_than_xor_equal(const gint& rhs, bool equal) const;

private:
    gint& add_self(const gint rhs);
    gint& add_digit_at_pos(size_t& pos, uint8_t digit);
    gint& subtract_digit_at_pos(size_t& pos, uint8_t digit);
    gint& multiply_by_digit(uint8_t digit);
    gint& multiply_by_by_adding(size_t rhs);
    typedef std::deque<uint8_t> gint_digits_t;
    gint_digits_t n_;
};

// more operators
inline bool operator==(const gint& lhs, const gint& rhs)
{
    return lhs.less_than_xor_equal(rhs, true);
}
inline bool operator!=(const gint& lhs, const gint& rhs)
{
    return !operator==(lhs,rhs);
}
inline bool operator< (const gint& lhs, const gint& rhs)
{
    return lhs.less_than_xor_equal(rhs, false);
}
inline bool operator> (const gint& lhs, const gint& rhs)
{
    return  operator< (rhs,lhs);
}
inline bool operator<=(const gint& lhs, const gint& rhs)
{
    return !operator> (lhs,rhs);
}
inline bool operator>=(const gint& lhs, const gint& rhs)
{
    return !operator< (lhs,rhs);
}
inline gint operator+ (gint lhs, const gint& rhs)
{
    lhs += rhs;
    return lhs;
}

#endif /* GINT_HPP_ */
