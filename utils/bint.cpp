/*
 * bint.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include <cstring>
#include <cctype>
#include <cmath>
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

size_t bint::real_size() const
{
    for ( size_t i = mem_.size() - 1; i < mem_.size(); --i )
    {
        if ( mem_[i] != 0 )
        {
            return i + 1;
        }
    }
    return 0;
}

bool bint::equals(const bint& rhs) const
{
    size_t this_real_size = real_size();
    size_t rhs_real_size = rhs.real_size();
    if ( this_real_size != rhs_real_size )
    {
        return false;
    }
    for ( size_t i = 0; i < this_real_size; ++i )
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
    size_t this_real_size = real_size();
    size_t rhs_real_size = rhs.real_size();
    if ( this_real_size > rhs_real_size )
    {
        return false;
    }
    if ( this_real_size < rhs_real_size )
    {
        return true;
    }
    for ( size_t i = this_real_size - 1; i < this_real_size; --i )
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

bint& bint::multiply_by(const bint& rhs)
{
    bint total;
    for ( size_t i = 0; i < rhs.mem_.size(); ++i )
    {
        bint inter(*this);
        inter.multiply_by(rhs.mem_[i]);
        inter <<= ( i * 8 );
        for ( size_t j = 0; j < i; ++j )
        {
            inter.mem_[j] = 0;
        }

        total += inter;
    }
    *this = total;
    return *this;
}

bint& bint::multiply_by(uint8_t num)
{
    if ( !num )
    {
        mem_.clear();
        return *this;
    }

    size_t limit = real_size();
    uint8_t overflow = 0;
    for ( size_t i = 0; i < limit; ++i )
    {
        uint16_t pre_result = static_cast<uint16_t>(mem_[i]) * num;
        mem_[i] = static_cast<uint8_t>(pre_result);
        add(overflow, i); // overflow from previous iteration
        overflow = pre_result >> 8;
    }
    if ( overflow )
    {
        add(overflow, limit); // overflow from previous iteration
    }

    return *this;
}

bint& bint::operator*=(const bint& rhs)
{
    return multiply_by(rhs);
}

bint& bint::divide_by(const bint& rhs)
{
    return *this;
}

bint& bint::operator/=(const bint& rhs)
{
    return divide_by(rhs);
}

bint& bint::bitshift_left(size_t i)
{
    if ( !i )
    {
        return *this;
    }

    size_t bytes = i/8;
    uint8_t bits = i%8;

    uint8_t left_shift = bits;
    uint8_t right_shift = 8 - ( bits ? bits : 8 );
    uint8_t high_mask = ( static_cast<uint8_t>(pow(2, bits)) - 1 )
                        << right_shift;
    if ( !high_mask )
    {
        // looks like we're moving full bytes
        // TODO forgo this if bits is zero???? check it out
        high_mask = ~high_mask;
    }
    uint8_t low_mask = ~high_mask;

    size_t r_size = real_size();
    size_t growth = bytes + ( bits ? 1 : 0 );
    size_t new_size = r_size + growth;
    mem_.resize(new_size);

    for ( size_t i = new_size - 1;
          i >= growth - 1 && i <= new_size - 1;
          --i )
    {
        size_t high_idx = i - growth + 1;
        size_t low_idx = high_idx - 1;
        uint8_t left_part = ( mem_[high_idx] & low_mask ) << left_shift;
        uint8_t right_part =
            ( ( low_idx >= new_size - 1 ? 0 : mem_[low_idx] ) & high_mask )
            >> right_shift;
        mem_[i] = left_part | right_part;
    }
    for ( size_t j = 0; j < growth - 1; ++j )
    {
        mem_[j] = 0;
    }

    return *this;
}

bint& bint::operator <<= (size_t i)
{
    return bitshift_left(i);
}

bint& bint::bitshift_right(size_t n)
{
    if ( !n )
    {
        return *this;
    }

    size_t bytes = n/8;
    uint8_t bits = n%8;

    uint8_t right_shift = bits;
    uint8_t left_shift = 8 - ( bits ? bits : 8 );
    uint8_t low_mask = ( static_cast<uint8_t>(pow(2, bits)) - 1 );
    uint8_t high_mask = ~low_mask;

    size_t orig_size = mem_.size();
    size_t new_size = real_size() - bytes;

    for ( size_t i = 0; i < new_size; ++i )
    {
        uint8_t right_part = ( mem_[i + bytes] & high_mask ) >> right_shift;
        uint8_t left_part =
            ( ( i + bytes + 1 >=  orig_size ? 0 : mem_[i + bytes + 1] ) &
              low_mask ) << left_shift;
        mem_[i] = left_part | right_part;
    }
    mem_.resize(new_size);
    return *this;
}

bint& bint::operator >>= (size_t i)
{
    return bitshift_right(i);
}

void bint::add(uint8_t num, size_t offset)
{
    if ( offset >= mem_.size() )
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

bint& bint::subtract(const bint& rhs)
{
    size_t orig = mem_.size();
    *this += ~rhs + 1;
    mem_.resize(orig);
    return *this;
}

bint& bint::operator-=(const bint& rhs)
{
    return subtract(rhs);
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

bint& bint::negate()
{
    for ( size_t i = 0; i < mem_.size(); ++i )
    {
        mem_[i] = ~mem_[i];
    }
    return *this;
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
    size_t limit = real_size();
    if ( !limit )
    {
        os << boost::format("%02x") % 0;
        return os;
    }
    for ( size_t i = limit - 1; i < limit; --i )
    {
        os << boost::format("%02x") % static_cast<int>(mem_[i]);
    }
    return os;
}

