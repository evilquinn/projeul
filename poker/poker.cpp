/*
 * poker.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "poker.hpp"

#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

void poker::make_hand(const std::string& hand_string, poker::hand& hand)
{
    hand.clear();
    boost::char_separator<char> sep(" ");
    boost::tokenizer< boost::char_separator<char> > card_strings(
                                                        hand_string,
                                                        sep);
    BOOST_FOREACH (const std::string& card_string, card_strings)
    {
        card c(card_string.c_str());
        hand.insert(c);
    }

    return;
}

int poker::game(const poker::hand& player1,
                const poker::hand& player2)
{
    return 0; // draw
}
