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
#include <iostream>

class gint
{
public:
    gint();
    explicit gint( size_t n );
    explicit gint( long int n );
    explicit gint( int n );
    gint( const gint& rhs );
    gint& operator=( gint rhs );
    virtual ~gint();

    friend void swap( gint& lhs, gint& rhs )
    {
        using std::swap;
        swap( lhs.n_, rhs.n_ );
        swap( lhs.is_negative, rhs.is_negative );
    }

    gint& add( const gint& rhs );
    gint& subtract( const gint& rhs );
    gint& multiply_by( const gint& mult_by );
    gint& divide_by( const gint& rhs );
    gint& pow( size_t rhs );
    gint abs() const;

    // operators
    gint& operator+=( const gint& rhs );
    gint& operator-=( const gint& rhs );
    gint& operator*=( const gint& rhs );
    gint& operator/=( const gint& rhs );
    gint& operator++();
    const gint operator++( int );
    gint& operator--();
    const gint operator--( int );

    // utility
    size_t to_size_t();
    gint& add_reverse_of( const gint& rhs );
    gint& reset();
    size_t sum_digits();
    size_t num_digits();
    bool is_palindrome();
    void print() const;
    std::ostream& stream_out( std::ostream& os ) const;
    bool less_than_xor_equal( const gint& rhs, bool equal ) const;

private:
    void construct_digits_from_positive( size_t n );
    gint& add_digit_at_pos( size_t& pos, uint8_t digit );
    gint& multiply_by_digit( uint8_t digit );
    typedef std::deque<uint8_t> gint_digits_t;
    gint_digits_t n_;
    bool is_negative{};
};

// more operators
inline bool operator==( const gint& lhs, const gint& rhs )
{
    return lhs.less_than_xor_equal( rhs, true );
}
inline bool operator!=( const gint& lhs, const gint& rhs )
{
    return !operator==( lhs, rhs );
}
inline bool operator<( const gint& lhs, const gint& rhs )
{
    return lhs.less_than_xor_equal( rhs, false );
}
inline bool operator>( const gint& lhs, const gint& rhs )
{
    return operator<( rhs, lhs );
}
inline bool operator<=( const gint& lhs, const gint& rhs )
{
    return !operator>( lhs, rhs );
}
inline bool operator>=( const gint& lhs, const gint& rhs )
{
    return !operator<( lhs, rhs );
}
inline gint operator+( gint lhs, const gint& rhs )
{
    lhs += rhs;
    return lhs;
}
inline gint operator-( gint lhs, const gint& rhs )
{
    lhs -= rhs;
    return lhs;
}
inline gint operator*( gint lhs, const gint& rhs )
{
    lhs *= rhs;
    return lhs;
}
inline gint operator/( gint lhs, const gint& rhs )
{
    lhs /= rhs;
    return lhs;
}
inline std::ostream& operator<<( std::ostream& os, const gint& obj )
{
    // write obj to stream
    return obj.stream_out( os );
}

#endif /* GINT_HPP_ */
