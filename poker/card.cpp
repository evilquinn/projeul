/*
 * card.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "card.hpp"

#include <string.h>
#include <iostream>

card::card(const char* string_value) :
    suit_(SUIT_UNINIT),
    value_(VALUE_UNINIT)
{
    // assume valid, EEK!
    value_ = char_to_value(string_value[0]);
    suit_ = char_to_suit(string_value[1]);
}

card::~card()
{
}


card::suit_k card::char_to_suit(char s)
{
    switch ( s )
    {
        case 'C' : return CLUBS;
        case 'H' : return HEARTS;
        case 'D' : return DIAMONDS;
        case 'S' : return SPADES;
        default  : return SUIT_UNINIT;
    }
}

card::value_k card::char_to_value(char v)
{
    switch ( v )
    {
        case '2' : return TWO;
        case '3' : return THREE;
        case '4' : return FOUR;
        case '5' : return FIVE;
        case '6' : return SIX;
        case '7' : return SEVEN;
        case '8' : return EIGHT;
        case '9' : return NINE;
        case 'T' : return TEN;
        case 'J' : return JACK;
        case 'Q' : return QUEEN;
        case 'K' : return KING;
        case 'A' : return ACE;
        default  : return VALUE_UNINIT;
    }
}
