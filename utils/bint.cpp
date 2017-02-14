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
    from_size_t(n);
}

bint::bint(const char* hex) :
    mem_(NULL),
    length_(0),
    capacity_(0)
{
    from_hex(hex);
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
    for ( size_t i = hex_length - 1; i < hex_length; --i )
    {
        if ( i == 0 )
        {
            // last char
            mem_[i/2] = hex_to_bin(hex[i]);
        }
        else
        {
            // take two chars at a time == 1 byte binary
            mem_[i/2] = (hex_to_bin(hex[i-1]) << 4) ^ hex_to_bin(hex[i]);
            --i;
        }
    }
    length_ = new_length;
}

void bint::from_size_t(size_t n)
{
    size_t new_length = sizeof(n);
    if ( new_length > capacity_ )
    {
        resize(new_length);
    }
    const uint8_t* bin_array = reinterpret_cast<const uint8_t*>(&n);
    for ( size_t i = new_length - 1; i < new_length; --i )
    {
        size_t mem_idx = new_length - 1;
        mem_[mem_idx - i] = bin_array[i];
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

void bint::print() const
{
    for ( size_t i = 0; i < length_; ++i )
    {
        printf("%02x", mem_[i]);
    }
    printf("\n");
}

std::ostream& bint::stream_out(std::ostream& os) const
{
    for ( size_t i = 0; i < length_; ++i )
    {
        os << boost::format("%02x") % static_cast<int>(mem_[i]);
    }
    os << std::dec;
    return os;
}
