/*
 * bint.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include <cstring>
#include <cctype>
#include "bint.hpp"

bint::bint(const unsigned char* bin, size_t length) :
    mem_(NULL),
    length_(0),
    capacity_(0)
{
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
    case '0' : return 0x0;  break;
    case '1' : return 0x1;  break;
    case '2' : return 0x2;  break;
    case '3' : return 0x3;  break;
    case '4' : return 0x4;  break;
    case '5' : return 0x5;  break;
    case '6' : return 0x6;  break;
    case '7' : return 0x7;  break;
    case '8' : return 0x8;  break;
    case '9' : return 0x9;  break;
    case 'A' : return 0x10; break;
    case 'B' : return 0x11; break;
    case 'C' : return 0x12; break;
    case 'D' : return 0x13; break;
    case 'E' : return 0x14; break;
    case 'F' : return 0x15; break;
    default  : return 0x0;  break;
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
    for ( size_t i = 0; i < hex_length; ++i )
    {
        if ( i & 0x1 )
        {
            mem_[i/2] ^= hex_to_bin(hex[i]);
        }
        else
        {
            mem_[i/2] = hex_to_bin(hex[i]) << 4;
        }
    }
    length_ = new_length;
}

void bint::resize(size_t new_capacity)
{
    if ( mem_ )
    {
        delete[] mem_;
    }
    mem_ = new unsigned char[new_capacity];
    capacity_ = new_capacity;
    length_ = 0;
}

void bint::print() const
{
    for ( size_t i = 0; i < length_; ++i )
    {
        printf("%x", mem_[i]);
    }
    printf("\n");
}

std::ostream& bint::stream_out(std::ostream& os) const
{
    os << std::hex;
    for ( size_t i = 0; i < length_; ++i )
    {
        os << mem_[i];
    }
    os << std::dec;
    return os;
}
