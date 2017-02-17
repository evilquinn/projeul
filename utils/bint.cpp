/*
 * bint.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include <cstring>
#include <cctype>
#include <iomanip>
#include <boost/format.hpp>
#include "bint.hpp"

bint::bint(const unsigned char* bin, size_t length) :
    mem_(new uint8_t[length]),
    length_(length),
    capacity_(length)
{
    memcpy(mem_, bin, length);
}

bint::bint(size_t n) :
    mem_(new uint8_t[sizeof(n)]),
    length_(sizeof(n)),
    capacity_(length_)
{
    memcpy(mem_, &n, length_);
}

bint::bint(const char* hex) :
    mem_(NULL),
    length_(0),
    capacity_(0)
{
    from_hex(hex);
}

bint::bint(const bint& b) :
    mem_(new uint8_t[b.capacity_]),
    length_(b.length_),
    capacity_(b.capacity_)
{
    memcpy(mem_, b.mem_, b.capacity_);
}

bint::~bint()
{
    if ( mem_ )
    {
        delete[] mem_;
    }
}

uint8_t bint::hex_to_bin(char hex)
{
    switch(toupper(hex))
    {
    case '0' : return 0x0; break;
    case '1' : return 0x1; break;
    case '2' : return 0x2; break;
    case '3' : return 0x3; break;
    case '4' : return 0x4; break;
    case '5' : return 0x5; break;
    case '6' : return 0x6; break;
    case '7' : return 0x7; break;
    case '8' : return 0x8; break;
    case '9' : return 0x9; break;
    case 'A' : return 0xA; break;
    case 'B' : return 0xB; break;
    case 'C' : return 0xC; break;
    case 'D' : return 0xD; break;
    case 'E' : return 0xE; break;
    case 'F' : return 0xF; break;
    default  : return 0x0; break;
    }
}

void bint::from_hex(const char* hex)
{
    size_t hex_length = strlen(hex);
    size_t new_length = ( hex_length + 1 ) / 2;
    if ( new_length > capacity_ )
    {
        resize(new_length);
    }
    size_t mem_idx = new_length - 1;
    for ( size_t i = hex_length - 1; i < hex_length; --i )
    {
        if ( i == 0 )
        {
            // last char
            mem_[mem_idx - (i/2)] = hex_to_bin(hex[i]);
        }
        else
        {
            // take two chars at a time == 1 byte binary
            mem_[mem_idx - (i/2)] =
                (hex_to_bin(hex[i-1]) << 4) ^ hex_to_bin(hex[i]);
            --i;
        }
    }
    length_ = new_length;
}

void bint::resize(size_t new_capacity)
{
    delete[] mem_;
    mem_ = new uint8_t[new_capacity];
    capacity_ = new_capacity;
    length_ = 0;
}

bool bint::equals(const bint& rhs) const
{
    if ( length_ != rhs.length_ )
    {
        return false;
    }
    for ( size_t i = 0; i < length_; ++i )
    {
        if ( mem_[i] != rhs.mem_[i] )
        {
            return false;
        }
    }
    return true;
}

bool bint::less_than(const bint& rhs) const
{
    if ( length_ > rhs.length_ )
    {
        return false;
    }
    if ( length_ < rhs.length_ )
    {
        return true;
    }
    for ( size_t i = length_ - 1; i < length_; --i )
    {
        if ( mem_[i] > rhs.mem_[i] )
        {
            return false;
        }
        if ( mem_[i] < rhs.mem_[i] )
        {
            return true;
        }
    }

    return false;
}

void bint::print() const
{
    for ( size_t i = length_ - 1; i < length_; --i )
    {
        printf("%02x", mem_[i]);
    }
    printf("\n");
}

std::ostream& bint::stream_out(std::ostream& os) const
{
    for ( size_t i = length_ - 1; i < length_; --i )
    {
        os << boost::format("%02x") % static_cast<int>(mem_[i]);
    }
    os << std::dec;
    return os;
}
