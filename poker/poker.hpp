/*
 * poker.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef POKER_HPP_
#define POKER_HPP_

#include <set>
#include <string>
#include <card.hpp>

namespace poker
{

typedef std::set<card> hand;

void make_hand(const std::string& hand_string, hand& hand);
int game(const hand& player1, const hand& player2);

class scored_hand
{
public:
    enum rank_k
    {
        RANK_UNINIT = 0,
        HIGH_CARD = 1,
        ONE_PAIR  = 2,
        TWO_PAIRS = 3,
        THREE_OF_KIND = 4,
        STRAIGHT = 5,
        FLUSH = 6,
        FOUR_OF_KIND = 7,
        STRAIGHT_FLUSH = 8,
        ROYAL_FLUSH = 9
    };
    scored_hand(const hand& hand);
    virtual ~scored_hand(){};

private:
    rank_k  rank_;
    hand    rank_cards_;
    hand    remaining_;

}; // class scored_hand

} // namespace poker

#endif /* POKER_HPP_ */
