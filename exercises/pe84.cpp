/*
 * pe84.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/tokenizer.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <pe84.hpp>
#include <sstream>
#include <utils.hpp>

namespace
{  // anonymous

namespace tile
{
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

}  // namespace tile

namespace community_chest
{
enum cc_enum
{
    A2GO,
    GO2J,
    OTH1,
    OTH2,
    OTH3,
    OTH4,
    OTH5,
    OTH6,
    OTH7,
    OTH8,
    OTH9,
    OTHA,
    OTHB,
    OTHC,
    OTHD,
    OTHE,
    MAX_CARD
};

}  // end namespace community_chest
namespace chance
{
enum ch_enum
{
    A2GO,
    GO2J,
    A2C1,
    A2E3,
    A2H2,
    A2R1,
    A2NR,
    A2RR,
    A2NU,
    BTHR,
    OTH1,
    OTH2,
    OTH3,
    OTH4,
    OTH5,
    OTH6,
    MAX_CARD
};

}  // end namespace chance
tile::tile_enum next_r( tile::tile_enum t )
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

tile::tile_enum next_u( tile::tile_enum t )
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

size_t random_in_range( size_t beg, size_t end )
{
    static boost::random::mt19937 rng(
        static_cast<unsigned int>( std::time( nullptr ) ) );
    boost::random::uniform_int_distribution<> dist( beg, end );
    return dist( rng );
}

community_chest::cc_enum select_cc()
{
    return static_cast<community_chest::cc_enum>( random_in_range(
        community_chest::A2GO, community_chest::MAX_CARD - 1 ) );
}

chance::ch_enum select_chance()
{
    return static_cast<chance::ch_enum>(
        random_in_range( chance::A2GO, chance::MAX_CARD - 1 ) );
}

struct two_die_result
{
    size_t result;
    bool is_double;
};

two_die_result roll_2_by( size_t die_sides )
{
    std::vector<size_t> rolls = { random_in_range( 1, die_sides ),
                                  random_in_range( 1, die_sides ) };
    return { rolls[0] + rolls[1], rolls[0] == rolls[1] };
}

}  // namespace

std::string& pe84::name() { return name_; }
void pe84::run()
{
    size_t num_squares = tile::MAX_TILE;
    std::map<size_t, size_t> tile_counts;
    size_t pos = tile::GO;

    size_t rolls = 1000000;
    std::map<size_t, size_t> results;
    size_t double_count = 0;
    for ( size_t i = 0; i < rolls; ++i )
    {
        auto roll = roll_2_by( 4 );
        if ( roll.is_double )
        {
            ++double_count;
        }
        else
        {
            double_count = 0;
        }
        if ( double_count >= 3 )
        {
            double_count = 0;
            pos          = tile::JAIL;
            tile_counts[pos] += 1;
            continue;
        }
        pos += roll.result;
        pos %= num_squares;
        switch ( pos )
        {
        case tile::CH1:
        case tile::CH2:
        case tile::CH3:
        {
            auto ch = select_chance();
            switch ( ch )
            {
            case chance::A2GO:
                pos = tile::GO;
                break;
            case chance::GO2J:
                pos = tile::JAIL;
                break;
            case chance::A2C1:
                pos = tile::C1;
                break;
            case chance::A2E3:
                pos = tile::E3;
                break;
            case chance::A2H2:
                pos = tile::H2;
                break;
            case chance::A2R1:
                pos = tile::R1;
                break;
            case chance::A2NR:
            case chance::A2RR:
                pos = next_r( static_cast<tile::tile_enum>( pos ) );
                break;
            case chance::A2NU:
                pos = next_u( static_cast<tile::tile_enum>( pos ) );
                break;
            case chance::BTHR:
                pos = ( ( num_squares + pos ) - 3 ) % num_squares;
                break;
            default: /* don't really care */
                break;
            }  // end switch
            break;
        }
        case tile::CC1:
        case tile::CC2:
        case tile::CC3:
        {
            auto cc = select_cc();
            switch ( cc )
            {
            case community_chest::A2GO:
                pos = tile::GO;
                break;
            case community_chest::GO2J:
                pos = tile::JAIL;
                break;
            default: /* don't really care */
                break;
            }  // end switch
            break;
        }
        case tile::G2J:
            pos = tile::JAIL;
            break;

        }  // end switch

        tile_counts[pos] += 1;
    }

    for ( auto count : tile_counts )
    {
        double prob = ( count.second / static_cast<double>( rolls ) ) * 100;
        if ( prob > 3.0 )
        {
            std::cout << count.first << ": " << count.second << "; "
                      << ( count.second / static_cast<double>( rolls ) ) * 100
                      << std::endl;
        }
    }
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
