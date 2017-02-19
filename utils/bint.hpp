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
//#include <functional>
//#include <algorithm>
#include <vector>

class bint
{
public:
    bint();
    bint(const unsigned char* binary, size_t length);
    bint(const char* hex);
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

    bint& transform(const bint& rhs, std::function<uint8_t(uint8_t, uint8_t)> op);

    bint& add(const bint& rhs);
    bint& operator += (const bint& rhs);

    bint& operator ^= (const bint& rhs);
    bint& operator &= (const bint& rhs);
    bint& operator |= (const bint& rhs);
/*    bint& subtract(const bint& rhs);
    bint& multiply_by(const bint& rhs);
    bint& divide_by(const bint& rhs);
    bint& pow(size_t rhs);
    bint abs() const;

    // operators
    bint& operator -= (const bint& rhs);
    bint& operator *= (const bint& rhs);
    bint& operator /= (const bint& rhs);
    bint& operator++();
    bint operator++(int);
    bint& operator--();
    bint operator--(int); */

    // utility
    std::ostream& stream_out(std::ostream& os) const;

    void print() const;

private:
    // copy from hex string
    void from_hex(const char* hex);
    // convert ascii hex char to binary
    uint8_t hex_to_bin(char hex);
    // add single uint8_t to mem
    void add(uint8_t num, size_t offset = 0);


    std::vector<uint8_t> mem_;
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
/*
inline bint operator- (bint lhs, const bint& rhs)
{
    lhs -= rhs;
    return lhs;
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
}*/
inline std::ostream& operator<<(std::ostream& os, const bint& obj)
{
    // write obj to stream
    return obj.stream_out(os);
}


#endif /* BINT_HPP_ */
