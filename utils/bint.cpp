/*
 * bint.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "bint.hpp"
#include <boost/format.hpp>
#include <cctype>
#include <cmath>
#include <cstring>
#include <iomanip>

bint::bint() : mem_( 0 ) {}
bint::bint( const unsigned char* bin, size_t length )
    : mem_( &bin[0], &bin[0] + length )
{
}

bint::bint( size_t n ) : mem_( sizeof( n ) )
{
    const unsigned char* bin   = reinterpret_cast<const unsigned char*>( &n );
    size_t               limit = mem_.size() - 1;
    for ( size_t i = 0; i < mem_.size(); ++i )
    {
        mem_[limit - i] = bin[i];
    }
}

bint::bint( const std::string& hex ) : mem_( ( hex.size() + 1 ) / 2 )
{
    from_hex( hex );
}

bint::bint( const bint& b ) : mem_( b.mem_.begin(), b.mem_.end() ) {}
bint& bint::operator=( bint rhs )
{
    swap( *this, rhs );
    return *this;
}

bint::~bint() = default;
uint8_t bint::hex_to_bin( char hex )
{
    switch ( toupper( hex ) )
    {
    case '0':
        return 0x0;
        break;
    case '1':
        return 0x1;
        break;
    case '2':
        return 0x2;
        break;
    case '3':
        return 0x3;
        break;
    case '4':
        return 0x4;
        break;
    case '5':
        return 0x5;
        break;
    case '6':
        return 0x6;
        break;
    case '7':
        return 0x7;
        break;
    case '8':
        return 0x8;
        break;
    case '9':
        return 0x9;
        break;
    case 'A':
        return 0xA;
        break;
    case 'B':
        return 0xB;
        break;
    case 'C':
        return 0xC;
        break;
    case 'D':
        return 0xD;
        break;
    case 'E':
        return 0xE;
        break;
    case 'F':
        return 0xF;
        break;
    default:
        return 0x0;
        break;
    }
}

void bint::from_hex( const std::string& hex )
{
    size_t hex_length = hex.size();
    size_t new_length = ( hex_length + 1 ) / 2;
    resize( new_length );
    for ( size_t i = hex_length - 1; i < hex_length; --i )
    {
        if ( i == 0 )
        {
            // last char
            mem_[i / 2] = hex_to_bin( hex[i] );
        }
        else
        {
            // take two chars at a time == 1 byte binary
            mem_[i / 2] =
                ( hex_to_bin( hex[i - 1] ) << 4 ) ^ hex_to_bin( hex[i] );
            --i;
        }
    }
}

size_t bint::real_size() const
{
    for ( size_t i = 0; i < mem_.size(); ++i )
    {
        if ( mem_[i] != 0 )
        {
            return mem_.size() - i;
        }
    }
    return 0;
}

bool bint::equals( const bint& rhs ) const
{
    size_t this_real_size = real_size();
    size_t rhs_real_size  = rhs.real_size();
    if ( this_real_size != rhs_real_size )
    {
        return false;
    }
    for ( size_t i = 0; i < this_real_size; ++i )
    {
        if ( *( mem_.rbegin() + i ) != *( rhs.mem_.rbegin() + i ) )
        {
            return false;
        }
    }
    return true;
}

bool bint::less_than( const bint& rhs ) const
{
    size_t this_real_size = real_size();
    size_t rhs_real_size  = rhs.real_size();
    if ( this_real_size > rhs_real_size )
    {
        return false;
    }
    if ( this_real_size < rhs_real_size )
    {
        return true;
    }
    long i_diff = mem_.size() - rhs.mem_.size();
    for ( size_t i = mem_.size() - this_real_size; i < mem_.size(); ++i )
    {
        if ( mem_[i] > rhs.mem_[i - i_diff] )
        {
            return false;
        }
        if ( mem_[i] < rhs.mem_[i - i_diff] )
        {
            return true;
        }
    }

    return false;
}

bint& bint::add( const bint& rhs )
{
    if ( this == &rhs )
    {
        bint temp( rhs );
        return add( temp );
    }

    for ( size_t i = 0; i < rhs.mem_.size(); ++i )
    {
        add( *( rhs.mem_.rbegin() + i ), i );
    }
    return *this;
}

bint& bint::operator+=( const bint& rhs ) { return add( rhs ); }
bint& bint::multiply_by( const bint& rhs )
{
    if ( rhs == static_cast<bint>( 0 ) )
    {
        mem_.clear();
        return *this;
    }

    bint total;
    for ( size_t i = 0; i < rhs.mem_.size(); ++i )
    {
        bint inter( *this );
        inter.multiply_by( *( rhs.mem_.rbegin() + i ) );
        inter <<= ( i * 8 );

        total += inter;
    }
    *this = total;
    return *this;
}

bint& bint::multiply_by( uint8_t num )
{
    if ( num == 0u )
    {
        mem_.clear();
        return *this;
    }

    size_t  limit    = real_size();
    uint8_t overflow = 0;
    for ( size_t i = 0; i < limit; ++i )
    {
        uint16_t pre_result =
            static_cast<uint16_t>( *( mem_.rbegin() + i ) ) * num;
        *( mem_.rbegin() + i ) = static_cast<uint8_t>( pre_result );
        add( overflow, i );  // overflow from previous iteration
        overflow = pre_result >> 8;
    }
    if ( overflow != 0u )
    {
        add( overflow, limit );  // overflow from previous iteration
    }

    return *this;
}

bint& bint::operator*=( const bint& rhs ) { return multiply_by( rhs ); }
bint& bint::divide_by_long_division( const bint& rhs, bint* rem )
{
    bint quotient( 0 );
    bint remainder( 0 );

    std::for_each( mem_.begin(), mem_.end(), [&]( mem_type::value_type val ) {
        remainder <<= 8;
        quotient <<= 8;
        remainder += bint( val );
        bint quotient_byte( 0 );

        while ( remainder >= rhs )
        {
            remainder -= rhs;
            ++quotient_byte;
        }
        quotient += quotient_byte;
    } );

    if ( rem != nullptr )
    {
        *rem = remainder;
    }

    *this = quotient;
    return *this;
}

bint& bint::divide_by( const bint& rhs, bint* remainder )
{
    if ( rhs == bint( 0ul ) )
    {
        throw std::invalid_argument( "can't divide by zero" );
    }
    if ( this == &rhs || *this == rhs )
    {
        *this = bint( 1 );
        if ( remainder != nullptr )
        {
            *remainder = bint( 0ul );
        }
        return *this;
    }
    return divide_by_long_division( rhs, remainder );
}

bint& bint::operator/=( const bint& rhs ) { return divide_by( rhs ); }
bint& bint::operator%=( const bint& rhs )
{
    bint remainder;
    divide_by( rhs, &remainder );
    *this = remainder;
    return *this;
}

bint& bint::bitshift_left( size_t n )
{
    if ( n == 0u )
    {
        return *this;
    }

    size_t  bytes = n / 8;
    uint8_t bits  = n % 8;

    uint8_t left_shift  = bits;
    uint8_t right_shift = 8 - bits;
    uint8_t low_mask = ( static_cast<uint8_t>(::pow( 2, right_shift ) ) - 1 );
    uint8_t high_mask = ~low_mask;

    if ( bytes != 0u )
    {
        mem_.insert( mem_.end(), bytes, 0 );
    }

    if ( bits == 0u )
    {
        return *this;
    }

    size_t r_size = real_size();
    if ( r_size == mem_.size() )
    {
        resize( ++r_size );
    }

    size_t start_i = mem_.size() - r_size - 1;
    for ( size_t i = start_i; i < mem_.size(); ++i )
    {
        size_t  high_idx  = i;
        size_t  low_idx   = high_idx + 1;
        uint8_t left_part = ( mem_[high_idx] & low_mask ) << left_shift;
        uint8_t right_part =
            ( ( low_idx >= mem_.size() ? 0 : mem_[low_idx] ) & high_mask ) >>
            right_shift;
        mem_[i] = left_part | right_part;
    }

    return *this;
}

bint& bint::operator<<=( size_t n ) { return bitshift_left( n ); }
bint& bint::bitshift_right( size_t n )
{
    if ( n == 0u )
    {
        return *this;
    }

    size_t  bytes = n / 8;
    uint8_t bits  = n % 8;

    if ( bytes != 0u )
    {
        mem_.erase( mem_.end() - bytes, mem_.end() );
    }

    if ( bits == 0u )
    {
        return *this;
    }

    uint8_t right_shift = bits;
    uint8_t left_shift  = 8 - bits;
    uint8_t low_mask = ( static_cast<uint8_t>(::pow( 2, right_shift ) ) - 1 );
    uint8_t high_mask = ~low_mask;

    for ( size_t i = mem_.size() - 1; i < mem_.size(); --i )
    {
        uint8_t right_part = ( mem_[i] & high_mask ) >> right_shift;
        uint8_t left_part =
            ( ( i - 1 >= mem_.size() ? 0 : mem_[i - 1] ) & low_mask )
            << left_shift;
        mem_[i] = left_part | right_part;
    }
    return *this;
}

bint& bint::operator>>=( size_t i ) { return bitshift_right( i ); }
void bint::add( uint8_t num, size_t offset )
{
    if ( offset >= mem_.size() )
    {
        mem_.insert( mem_.begin(), num );
        return;
    }
    uint16_t pre_result =
        static_cast<uint16_t>( *( mem_.rbegin() + offset ) ) + num;
    *( mem_.rbegin() + offset ) = static_cast<uint8_t>( pre_result );
    uint8_t overflow            = pre_result >> 8;
    if ( overflow != 0u )
    {
        add( overflow, offset + 1 );
    }
}

void bint::resize_chararray( size_t n )
{
    if ( n > mem_.size() )
    {
        size_t diff = n - mem_.size();
        mem_.insert( mem_.end(), diff, 0 );
    }
    else if ( n < mem_.size() )
    {
        size_t diff = mem_.size() - n;
        mem_.erase( mem_.end() - diff, mem_.end() );
    }
}

void bint::resize( size_t n )
{
    if ( n > mem_.size() )
    {
        size_t diff = n - mem_.size();
        mem_.insert( mem_.begin(), diff, 0 );
    }
    else if ( n < mem_.size() )
    {
        size_t diff = mem_.size() - n;
        mem_.erase( mem_.begin(), mem_.begin() + diff );
    }
}

size_t bint::size() const { return mem_.size(); }
bint& bint::subtract( const bint& rhs )
{
    const bint* sub = &rhs;
    bint        temp;
    if ( mem_.size() < rhs.mem_.size() )
    {
        resize( rhs.mem_.size() );
    }
    else if ( mem_.size() > rhs.mem_.size() )
    {
        temp = rhs;
        temp.resize( mem_.size() );
        sub = &temp;
    }
    size_t orig = mem_.size();
    *this += ~( *sub ) + bint( 1 );
    resize( orig );
    return *this;
}

bint& bint::operator++() { return *this += bint( 1 ); }
bint  bint::operator++( int )
{
    bint tmp( *this );
    *this += bint( 1 );
    return tmp;
}

bint& bint::operator--() { return *this -= bint( 1 ); }
bint  bint::operator--( int )
{
    bint tmp( *this );
    *this -= bint( 1 );
    return tmp;
}

bint& bint::operator-=( const bint& rhs ) { return subtract( rhs ); }
bint& bint::pow( const bint& rhs )
{
    if ( rhs == bint( 0 ) )
    {
        *this = bint( 1 );
        return *this;
    }
    bint mult( *this );
    bint limit( rhs );
    --limit;
    for ( bint i( 0 ); i < limit; ++i )
    {
        multiply_by( mult );
    }
    return *this;
}

bint& bint::transform( const bint& rhs,
                       std::function<uint8_t( uint8_t, uint8_t )> op )
{
    if ( rhs.mem_.size() > mem_.size() )
    {
        resize( rhs.mem_.size() );
    }

    for ( size_t i = rhs.mem_.size() - 1; i < rhs.mem_.size(); --i )
    {
        mem_[i] = op( mem_[i], rhs.mem_[i] );
    }
    return *this;
}

bint& bint::operator^=( const bint& rhs )
{
    return transform( rhs, std::bit_xor<uint8_t>() );
}

bint& bint::operator&=( const bint& rhs )
{
    return transform( rhs, std::bit_and<uint8_t>() );
}

bint& bint::operator|=( const bint& rhs )
{
    return transform( rhs, std::bit_or<uint8_t>() );
}

bint& bint::negate()
{
    std::for_each( mem_.begin(), mem_.end(), []( mem_type::reference val ) {
        val = ~val;
    } );

    return *this;
}

bint::operator size_t() const
{
    mem_type rev( mem_.rbegin(), mem_.rbegin() + sizeof( size_t ) );
    return *( reinterpret_cast<const size_t*>( &rev[0] ) );
}

bint::operator unsigned char*()
{
    return reinterpret_cast<unsigned char*>( &mem_[0] );
}

bint::operator const unsigned char*() const
{
    return reinterpret_cast<const unsigned char*>( &mem_[0] );
}

void bint::print() const
{
    std::for_each( mem_.begin(), mem_.end(), []( const uint8_t val ) {
        printf( "%02x", val );
    } );
    printf( "\n" );
}

std::ostream& bint::stream_out( std::ostream& os ) const
{
    if ( real_size() == 0u )
    {
        return os;
    }

    std::for_each( mem_.begin(), mem_.end(), [&]( int e ) {
        os << boost::format( "%02x" ) % e;
    } );
    return os;
}
