/*
 * card.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef CARD_HPP_
#define CARD_HPP_

#include <stddef.h>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <deque>

#define PRIME_SIEVE_MAX_PRIME 67000000

class card
{
public:
    enum suit_k
    {
        SUIT_UNINIT,
        HEARTS,
        DIAMONDS,
        SPADES,
        CLUBS
    };

    enum value_k
    {
        VALUE_UNINIT = 0,
        TWO   = 2,
        THREE = 3,
        FOUR  = 4,
        FIVE  = 5,
        SIX   = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE  = 9,
        TEN   = 10,
        JACK  = 11,
        QUEEN = 12,
        KING  = 13,
        ACE   = 14
    };

    card(const char* string_value);
    virtual ~card();

    suit_k  suit_;
    value_k value_;
    bool operator<(const card& rhs) const;

private:
    suit_k char_to_suit(char s);
    value_k char_to_value(char v);
};

#endif /* CARD_HPP_ */
