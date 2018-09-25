/*
 * pe84.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe84.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <utils.hpp>
#include <sstream>

namespace { // anonymous

namespace tile {

    enum tile_enum
    {
        GO,
        A1,
        CC1,
        A2,
        T1,
        R1,
        B1,
        CH1,
        B2,
        B3,
        JAIL,
        C1,
        U1,
        C2,
        C3,
        R2,
        D1,
        CC2,
        D2,
        D3,
        FP,
        E1,
        CH2,
        E2,
        E3,
        R3,
        F1,
        F2,
        U2,
        F3,
        G2J,
        G1,
        G2,
        CC3,
        G3,
        R4,
        CH3,
        H1,
        T2,
        H2,
        MAX_TILE
    };

    std::string to_string(size_t t)
    {
        switch ( t )
        {
        case GO   :  return "GO";
        case A1   :  return "A1";
        case CC1  :  return "CC1";
        case A2   :  return "A2";
        case T1   :  return "T1";
        case R1   :  return "R1";
        case B1   :  return "B1";
        case CH1  :  return "CH1";
        case B2   :  return "B2";
        case B3   :  return "B3";
        case JAIL :  return "JAIL";
        case C1   :  return "C1";
        case U1   :  return "U1";
        case C2   :  return "C2";
        case C3   :  return "C3";
        case R2   :  return "R2";
        case D1   :  return "D1";
        case CC2  :  return "CC2";
        case D2   :  return "D2";
        case D3   :  return "D3";
        case FP   :  return "FP";
        case E1   :  return "E1";
        case CH2  :  return "CH2";
        case E2   :  return "E2";
        case E3   :  return "E3";
        case R3   :  return "R3";
        case F1   :  return "F1";
        case F2   :  return "F2";
        case U2   :  return "U2";
        case F3   :  return "F3";
        case G2J  :  return "G2J";
        case G1   :  return "G1";
        case G2   :  return "G2";
        case CC3  :  return "CC3";
        case G3   :  return "G3";
        case R4   :  return "R4";
        case CH3  :  return "CH3";
        case H1   :  return "H1";
        case T2   :  return "T2";
        case H2   :  return "H2";
        default   :  return "Uknown tile: " + t;
        } // end switch
    }
} // end namspace tile

tile::tile_enum next_r(tile::tile_enum t)
{
    if ( t < tile::R1 )
    {
        return tile::R1;
    }
    else if ( t < tile::R2 )
    {
        return tile::R2;
    }
    else if ( t < tile::R3 )
    {
        return tile::R3;
    }
    else if ( t < tile::R4 )
    {
        return tile::R4;
    }
    else
    {
        return tile::R1;
    }
}

tile::tile_enum next_u(tile::tile_enum t)
{
    if ( t < tile::U1 )
    {
        return tile::U1;
    }
    else if ( t < tile::U2 )
    {
        return tile::U2;
    }
    else
    {
        return tile::U1;
    }
}

} // end namespace anonymous

std::string& pe84::name() { return name_; }
void         pe84::run()
{
    size_t result = 0;
    size_t num_squares = tile::MAX_TILE;
    std::vector<double> probs(num_squares, 2.5);

    // if land on CHx, could go to:
    //   1/16 GO
    //   1/16 JAIL
    //   1/16 C1
    //   1/16 E3
    //   1/16 H2
    //   1/16 R1
    //   1/16 Next R
    //   1/16 Next R
    //   1/16 Next U
    //   1/16 Back 3
    double swap = 0;
    double card_prob = 1.0/16.0;

    auto CHes = { tile::CH1, tile::CH2, tile::CH3 };
    for ( auto ch : CHes )
    {
        swap = probs[ch] * card_prob;
        probs[tile::GO] += swap;
        probs[tile::JAIL] += swap;
        probs[tile::C1] += swap;
        probs[tile::E3] += swap;
        probs[tile::H2] += swap;
        probs[tile::R1] += swap;
        probs[next_r(ch)] += swap;
        probs[next_r(ch)] += swap;
        probs[next_u(ch)] += swap;
        probs[ch-3] += swap;
        probs[ch] -= swap * 10;
    }

    // if land on CCx, could go to:
    //   1/16 GO
    //   1/16 JAIL
    auto CCs = { tile::CC1, tile::CC2, tile::CC3 };
    for ( auto cc : CCs )
    {
        swap = probs[cc] * card_prob;
        probs[tile::GO] += swap;
        probs[tile::JAIL] += swap;
        probs[cc] -= swap * 2;
    }

    // can't land on G2J
    probs[tile::JAIL] += probs[tile::G2J];
    probs[tile::G2J] = 0;

    for(size_t i = 0; i < tile::MAX_TILE; ++i)
    {
        std::cout << tile::to_string(i) << ":    " << probs[i] << std::endl;
    }
    std::cout << "result: " << result << std::endl;
}

/*
 * A player starts on the GO square and adds the scores on two 6-sided
 * dice to determine the number of squares they advance in a clockwise
 * direction. Without any further rules we would expect to visit each
 * square with equal probability: 2.5%. However, landing on
 * G2J (Go To Jail), CC (community chest), and CH (chance) changes this
 * distribution.
 *
 * In addition to G2J, and one card from each of CC and CH, that orders
 * the player to go directly to jail, if a player rolls three consecutive
 * doubles, they do not advance the result of their 3rd roll.
 * Instead they proceed directly to jail.
 *
 * At the beginning of the game, the CC and CH cards are shuffled. When a
 * player lands on CC or CH they take a card from the top of the respective
 * pile and, after following the instructions, it is returned to the bottom
 * of the pile. There are sixteen cards in each pile, but for the purpose
 * of this problem we are only concerned with cards that order a movement;
 * any instruction not concerned with movement will be ignored and the
 * player will remain on the CC/CH square.
 *
 *  Community Chest (2/16 cards):
 *    Advance to GO
 *    Go to JAIL
 *  Chance (10/16 cards):
 *    Advance to GO
 *    Go to JAIL
 *    Go to C1
 *    Go to E3
 *    Go to H2
 *    Go to R1
 *    Go to next R (railway company)
 *    Go to next R
 *    Go to next U (utility company)
 *    Go back 3 squares.
 *
 * The heart of this problem concerns the likelihood of visiting a
 * particular square. That is, the probability of finishing at that square
 * after a roll. For this reason it should be clear that, with the
 * exception of G2J for which the probability of finishing on it is zero,
 * the CH squares will have the lowest probabilities, as 5/8 request a
 * movement to another square, and it is the final square that the player
 * finishes at on each roll that we are interested in. We shall make no
 * distinction between "Just Visiting" and being sent to JAIL, and we
 * shall also ignore the rule about requiring a double to
 * "get out of jail", assuming that they pay to get out on their next turn.
 *
 * By starting at GO and numbering the squares sequentially from 00 to 39
 * we can concatenate these two-digit numbers to produce strings that
 * correspond with sets of squares.
 *
 * Statistically it can be shown that the three most popular squares,
 * in order, are JAIL (6.24%) = Square 10, E3 (3.18%) = Square 24, and
 * GO (3.09%) = Square 00. So these three most popular squares can be
 * listed with the six-digit modal string: 102400.
 *
 * If, instead of using two 6-sided dice, two 4-sided dice are used,
 * find the six-digit modal string.
 */