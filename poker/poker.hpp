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
    scored_hand(hand);
    virtual ~scored_hand(){};

private:
    rank_k  rank_;
    hand    remaining_;

} // class scored_hand

} // namespace poker

#endif /* POKER_HPP_ */
