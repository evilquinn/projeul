/*
 * bint.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef BINT_HPP_
#define BINT_HPP_

#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

class bint
{
public:
    bint();
    bint(const unsigned char* binary, size_t length);
    bint(const std::string& hex);
    bint(size_t n);
    bint(const bint& b);
    bint& operator = (bint rhs);

    friend void swap(bint& lhs, bint& rhs)
    {
        using std::swap;
        swap(lhs.mem_, rhs.mem_);
    }

    virtual ~bint();

    // equality testing
    bool equals(const bint& rhs) const;
    bool less_than(const bint& rhs) const;

    bint& transform(const bint& rhs,
                    std::function<uint8_t(uint8_t, uint8_t)> op);

    bint& add(const bint& rhs);
    bint& subtract(const bint& rhs);
    bint& multiply_by(const bint& rhs);
    bint& divide_by(const bint& rhs, bint* remainder = NULL);
    bint& divide_by_long_division(const bint& rhs, bint* remainder = NULL);
    bint& operator += (const bint& rhs);
    bint& operator -= (const bint& rhs);
    bint& operator *= (const bint& rhs);
    bint& operator /= (const bint& rhs);
    bint& operator %= (const bint& rhs);

    bint& bitshift_left(size_t i);
    bint& operator <<= (size_t rhs);
    bint& bitshift_right(size_t i);
    bint& operator >>= (size_t rhs);

    bint& negate();

    bint& operator ^= (const bint& rhs);
    bint& operator &= (const bint& rhs);
    bint& operator |= (const bint& rhs);
    bint& pow(const bint& rhs);
//    bint abs() const;

    bint& operator++();
    bint operator++(int);
    bint& operator--();
    bint operator--(int);

    // utility
    std::ostream& stream_out(std::ostream& os) const;

    void print() const;

    explicit operator size_t() const;
    explicit operator unsigned char*();

private:
    // copy from hex string
    void from_hex(const std::string& hex);
    // convert ascii hex char to binary
    uint8_t hex_to_bin(char hex);
    // add single uint8_t to mem
    void add(uint8_t num, size_t offset = 0);
    // multiply single uint8_t to mem
    bint& multiply_by(uint8_t num);
    // determine number of used bytes
    size_t real_size() const;


    std::vector<uint8_t> mem_;
    std::vector<uint8_t> rev_mem_;
};

// more operators
inline bool operator==(const bint& lhs, const bint& rhs)
{
    return lhs.equals(rhs);
}
inline bool operator!=(const bint& lhs, const bint& rhs)
{
    return !operator==(lhs,rhs);
}
inline bool operator< (const bint& lhs, const bint& rhs)
{
    return lhs.less_than(rhs);
}
inline bool operator> (const bint& lhs, const bint& rhs)
{
    return  operator< (rhs,lhs);
}
inline bool operator<=(const bint& lhs, const bint& rhs)
{
    return !operator> (lhs,rhs);
}
inline bool operator>=(const bint& lhs, const bint& rhs)
{
    return !operator< (lhs,rhs);
}
inline bint operator+ (bint lhs, const bint& rhs)
{
    lhs += rhs;
    return lhs;
}
inline bint operator^ (bint lhs, const bint& rhs)
{
    lhs ^= rhs;
    return lhs;
}
inline bint operator& (bint lhs, const bint& rhs)
{
    lhs &= rhs;
    return lhs;
}
inline bint operator| (bint lhs, const bint& rhs)
{
    lhs |= rhs;
    return lhs;
}
inline bint operator- (bint lhs, const bint& rhs)
{
    lhs -= rhs;
    return lhs;
}
inline bint operator~ (bint lhs)
{
    return lhs.negate();
}
inline bint operator* (bint lhs, const bint& rhs)
{
    lhs *= rhs;
    return lhs;
}
inline bint operator/ (bint lhs, const bint& rhs)
{
    lhs /= rhs;
    return lhs;
}
inline bint operator% (bint lhs, const bint& rhs)
{
    lhs %= rhs;
    return lhs;
}
inline std::ostream& operator<<(std::ostream& os, const bint& obj)
{
    // write obj to stream
    return obj.stream_out(os);
}
inline bint operator<<(bint lhs, size_t rhs)
{
    lhs.bitshift_left(rhs);
    return lhs;
}
inline bint operator>>(bint lhs, size_t rhs)
{
    lhs.bitshift_right(rhs);
    return lhs;
}


#endif /* BINT_HPP_ */
