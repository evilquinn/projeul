/*
 * card.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef CARD_HPP_
#define CARD_HPP_

#include <string>

class card
{
public:
    enum suit_k
    {
        SUIT_UNINIT = 0,
        HEARTS,
        DIAMONDS,
        SPADES,
        CLUBS
    };

    enum value_k
    {
        VALUE_UNINIT = 0,
        TWO          = 2,
        THREE        = 3,
        FOUR         = 4,
        FIVE         = 5,
        SIX          = 6,
        SEVEN        = 7,
        EIGHT        = 8,
        NINE         = 9,
        TEN          = 10,
        JACK         = 11,
        QUEEN        = 12,
        KING         = 13,
        ACE          = 14
    };

    explicit card( const std::string& string_value );

    suit_k  suit_;
    value_k value_;
    int     ival_;
    bool operator<( const card& rhs ) const;

private:
    suit_k char_to_suit( const char s ) const;
    value_k char_to_value( const char v ) const;
    int char_to_int( const char v ) const;
};

#endif /* CARD_HPP_ */
