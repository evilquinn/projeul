/*
 * card.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "card.hpp"

#include <string.h>
#include <iostream>


card::card() :
    suit_(SUIT_UNINIT),
    value_(VALUE_UNINIT),
    ival_(0)
{}

card::card(const card& copy) :
    suit_(copy.suit_),
    value_(copy.value_),
    ival_(copy.ival_)
{}

card::card(const std::string& string_value) :
    suit_(SUIT_UNINIT),
    value_(VALUE_UNINIT),
    ival_(0)
{
    // assume valid, EEK!
    value_ = char_to_value(string_value[0]);
    ival_  = char_to_int(string_value[0]);
    suit_ = char_to_suit(string_value[1]);

}

card::~card()
{
}


card::suit_k card::char_to_suit(const char s) const
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

int card::char_to_int(const char v) const
{
    switch ( v )
    {
        case '2' : return 2;
        case '3' : return 3;
        case '4' : return 4;
        case '5' : return 5;
        case '6' : return 6;
        case '7' : return 7;
        case '8' : return 8;
        case '9' : return 9;
        case 'T' : return 10;
        case 'J' : return 11;
        case 'Q' : return 12;
        case 'K' : return 13;
        case 'A' : return 14;
        default  : return 0;
    }
}


card::value_k card::char_to_value(const char v) const
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

bool card::operator<(const card& rhs) const
{
    bool result = value_ == rhs.value_ ?
                      suit_  < rhs.suit_ :
                      value_ < rhs.value_ ;
    return result;
}
