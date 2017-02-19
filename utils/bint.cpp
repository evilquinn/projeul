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

bint::bint() :
    mem_()
{
}

bint::bint(const unsigned char* bin, size_t length) :
    mem_(&bin[0], &bin[0] + length)
{
}

bint::bint(size_t n) :
    mem_(sizeof(n))
{
    const unsigned char* bin = reinterpret_cast<const unsigned char*>(&n);
    for ( size_t i = 0; i < mem_.size(); ++i )
    {
        mem_[i] = bin[i];
    }
}

bint::bint(const char* hex) :
    mem_((strlen(hex) + 1) / 2)
{
    from_hex(hex);
}

bint::bint(const bint& b) :
    mem_(b.mem_.begin(), b.mem_.end())
{
}

bint& bint::operator=(bint rhs)
{
    swap(*this, rhs);
    return *this;
}

bint::~bint()
{
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
    mem_.resize(new_length);
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
}

bool bint::equals(const bint& rhs) const
{
    if ( mem_.size() != rhs.mem_.size() )
    {
        return false;
    }
    for ( size_t i = 0; i < mem_.size(); ++i )
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
    if ( mem_.size() > rhs.mem_.size() )
    {
        return false;
    }
    if ( mem_.size() < rhs.mem_.size() )
    {
        return true;
    }
    for ( size_t i = mem_.size() - 1; i < mem_.size(); --i )
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

bint& bint::add(const bint& rhs)
{
    if ( this == &rhs )
    {
        bint temp(rhs);
        return add(temp);
    }

    for ( size_t i = 0; i < rhs.mem_.size(); ++i )
    {
        add(rhs.mem_[i], i);
    }
    return *this;
}

bint& bint::operator += (const bint& rhs)
{
    return add(rhs);
}

void bint::add(uint8_t num, size_t offset)
{
    if ( offset > mem_.size() )
    {
        mem_.push_back(num);
        return;
    }
    uint16_t pre_result = static_cast<uint16_t>(mem_[offset]) + num;
    mem_[offset] = static_cast<uint8_t>(pre_result);
    uint8_t overflow = pre_result >> 8;
    if ( overflow )
    {
        add(overflow, offset + 1);
    }
}

bint& bint::transform(const bint& rhs, std::function<uint8_t(uint8_t, uint8_t)> op)
{
    if ( rhs.mem_.size() > mem_.size() )
    {
        mem_.resize(rhs.mem_.size());
    }

    for ( size_t i = 0; i < mem_.size(); ++i )
    {
        mem_[i] = op(mem_[i], rhs.mem_[i]);
    }
    return *this;
}


bint& bint::operator ^= (const bint& rhs)
{
    return transform(rhs, std::bit_xor<uint8_t>());
}

bint& bint::operator &= (const bint& rhs)
{
    return transform(rhs, std::bit_and<uint8_t>());
}

bint& bint::operator |= (const bint& rhs)
{
    return transform(rhs, std::bit_or<uint8_t>());
}


void bint::print() const
{
    for ( size_t i = mem_.size() - 1; i < mem_.size(); --i )
    {
        printf("%02x", mem_[i]);
    }
    printf("\n");
}

std::ostream& bint::stream_out(std::ostream& os) const
{
    for ( size_t i = mem_.size() - 1; i < mem_.size(); --i )
    {
        os << boost::format("%02x") % static_cast<int>(mem_[i]);
    }
    os << std::dec;
    return os;
}

