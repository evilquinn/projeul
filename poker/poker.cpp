/*
 * poker.cpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#include "poker.hpp"

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>

void poker::make_hand( const std::string& hand_string, poker::hand& hand )
{
    hand.clear();
    boost::char_separator<char> sep( " " );
    boost::tokenizer<boost::char_separator<char> > card_strings( hand_string,
                                                                 sep );
    BOOST_FOREACH ( const std::string& card_string, card_strings )
    {
        card c( card_string );
        hand.insert( c );
    }
}

poker::scored_hand::scored_hand( const poker::hand& hand )
    : rank_( RANK_UNINIT ), hand_( hand )
{
    analyse_for_straight_flush();

    // analyse for some of a kind
    card_count_map_t seen_cards;
    BOOST_FOREACH ( const card& c, hand_ )
    {
        seen_cards[c.ival_].insert( c );
    }
    BOOST_FOREACH ( const card_count_map_t::value_type& card_count,
                    seen_cards )
    {
        if ( card_count.second.size() > 4 )
        {
            std::cout << "WTF!!!" << std::endl;
        }
        else if ( card_count.second.size() == 4 )
        {
            if ( upgrade_rank( poker::scored_hand::FOUR_OF_KIND ) )
            {
                rank_cards_ = card_count.second;
            }
        }
        else if ( card_count.second.size() == 3 )
        {
            if ( upgrade_rank( poker::scored_hand::THREE_OF_KIND ) )
            {
                rank_cards_.insert( card_count.second.begin(),
                                    card_count.second.end() );
            }
        }
        else if ( card_count.second.size() == 2 )
        {
            if ( upgrade_rank( poker::scored_hand::ONE_PAIR ) )
            {
                rank_cards_.insert( card_count.second.begin(),
                                    card_count.second.end() );
            }
        }
        else
        {
            upgrade_rank( poker::scored_hand::HIGH_CARD );
            remaining_.insert( card_count.second.begin(),
                               card_count.second.end() );
        }
    }
}

int poker::scored_hand::play( const poker::scored_hand& enemy )
{
    // -1 for I Lose, 0 for draw, +1 for I Win, I == this

    if ( rank_ > enemy.rank_ )
    {
        return 1;
    }
    if ( rank_ == enemy.rank_ )
    {
        if ( !rank_cards_.empty() && !enemy.rank_cards_.empty() )
        {
            const hand::reverse_iterator my_highest_rank =
                rank_cards_.rbegin();
            const hand::reverse_iterator his_highest_rank =
                enemy.rank_cards_.rbegin();
            if ( my_highest_rank->value_ < his_highest_rank->value_ )
            {
                return -1;
            }
            if ( his_highest_rank->value_ < my_highest_rank->value_ )
            {
                return 1;
            }
        }

        // rank is same, and winning rank cards are same,
        // need to check HIGH_CARD
        if ( !remaining_.empty() && !enemy.remaining_.empty() )
        {
            const hand::reverse_iterator my_highest_remaining =
                remaining_.rbegin();
            const hand::reverse_iterator his_highest_remaining =
                enemy.remaining_.rbegin();
            if ( my_highest_remaining->value_ <
                 his_highest_remaining->value_ )
            {
                return -1;
            }
            if ( his_highest_remaining->value_ <
                 my_highest_remaining->value_ )
            {
                return 1;
            }
        }

        return 0;
    }

    return -1;
}

bool poker::scored_hand::upgrade_rank( poker::scored_hand::rank_k new_rank )
{
    if ( rank_ == poker::scored_hand::ONE_PAIR )
    {
        if ( new_rank == poker::scored_hand::THREE_OF_KIND )
        {
            rank_ = poker::scored_hand::FULL_HOUSE;
            return true;
        }
        if ( new_rank == poker::scored_hand::ONE_PAIR )
        {
            rank_ = poker::scored_hand::TWO_PAIRS;
            return true;
        }
    }
    else if ( rank_ == poker::scored_hand::THREE_OF_KIND &&
              new_rank == poker::scored_hand::ONE_PAIR )
    {
        rank_ = poker::scored_hand::FULL_HOUSE;
        return true;
    }

    if ( rank_ < new_rank )
    {
        rank_ = new_rank;
        return true;
    }
    return false;
}

void poker::scored_hand::analyse_for_straight_flush()
{
    // check for a straight and / or flush, cache a royal if we see it
    bool flush       = true;
    bool straight    = true;
    bool starting    = true;
    const card* last = nullptr;
    BOOST_FOREACH ( const card& c, hand_ )
    {
        if ( starting )
        {
            last     = &c;
            starting = false;
            continue;
        }

        if ( c.ival_ == last->ival_ + 1 )
        {
        }
        else
        {
            straight = false;
        }

        if ( c.suit_ != last->suit_ )
        {
            flush = false;
        }

        last = &c;
    }

    if ( straight )
    {
        if ( flush )
        {
            if ( last->value_ == card::ACE )
            {
                rank_       = ROYAL_FLUSH;
                rank_cards_ = hand_;
            }
            else
            {
                rank_       = STRAIGHT_FLUSH;
                rank_cards_ = hand_;
            }
        }
        else
        {
            rank_       = STRAIGHT;
            rank_cards_ = hand_;
        }
    }
    else if ( flush )
    {
        rank_       = FLUSH;
        rank_cards_ = hand_;
    }
};

int poker::game( const poker::hand& player1, const poker::hand& player2 )
{
    // p1 wins == -1; draw == 0; p2 wins == 1
    scored_hand p1( player1 );
    scored_hand p2( player2 );
    return p2.play( p1 );
}
