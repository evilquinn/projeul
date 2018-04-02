/*
 * pe51.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe51.hpp"
#include <ctype.h>
#include <stdio.h>
#include <boost/foreach.hpp>
#include <cmath>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include "utils.hpp"

#define PE51_BEGIN 10000

std::string& pe51::name() { return name_; }
void         pe51::run()
{
    /*
     *
     * By replacing the 1st digit of the 2-digit number *3, it turns out that
     * six of the nine possible values:
     *   13, 23, 43, 53, 73, and 83,
     * are all prime.
     *
     * By replacing the 3rd and 4th digits of 56**3 with the same digit, this
     * 5-digit number is the first example having seven primes among the ten
     * generated numbers, yielding the family:
     *   56003, 56113, 56333, 56443, 56663, 56773, and 56993.
     * Consequently 56003, being the first member of this family, is the
     * smallest prime with this property.
     *
     * Find the smallest prime which, by replacing part of the number (not
     * necessarily adjacent digits) with the same digit, is part of an eight
     * prime value family.
     *
     *
     */

    primes_        = prime_sieve( PE51_MAX_PRIMES );
    size_t current = primes_.next_prime( PE51_BEGIN );
    bool   done    = false;

    typedef std::map<size_t, std::set<int>> checked_map_t;
    checked_map_t already_checked;

    size_t best_count    = 0;
    size_t best_smallest = 999999999;

    while ( !done )
    {
        // check is got two zeros
        digit_count_map_t   digit_count;
        digit_pattern_map_t digit_pattern;

        BOOST_FOREACH ( digit_count_map_t::value_type& p, digit_count )
        {
            if ( p.second >= 2 )
            {
                checked_map_t::iterator it = already_checked.find( current );
                if ( it != already_checked.end() &&
                     it->second.count( p.first ) > 0 )
                {
                    continue;
                }

                // p.first is the digit we're swapping out, will tell us how
                // many to "go back" till the "zero" potential
                size_t curr_digit_pattern = digit_pattern[p.first];

                size_t sub_to_zero      = p.first * curr_digit_pattern;
                size_t curr_of_current  = current - sub_to_zero;
                size_t current_count    = 0;
                size_t current_smallest = current;
                for ( int i = 0; i < 10; ++i )
                {
                    if ( curr_of_current < PE51_BEGIN )
                    {
                    }
                    else if ( primes_.is_prime( curr_of_current ) )
                    {
                        already_checked[curr_of_current].insert( i );
                        ++current_count;
                        if ( curr_of_current < current_smallest )
                        {
                            current_smallest = curr_of_current;
                        }
                    }
                    curr_of_current += curr_digit_pattern;
                }

                if ( current_count > best_count )
                {
                    best_count    = current_count;
                    best_smallest = current_smallest;

                    std::cout << "new best: " << best_smallest << " has "
                              << best_count << std::endl;
                }
            }
        }

        current = primes_.next_prime( current );
        if ( best_count == 8 || current >= PE51_MAX_PRIMES )
        {
            done = true;
        }
    }

    std::cout << name() << std::endl;
    std::cout << "best count    : " << best_count << std::endl;
    std::cout << "best smallest : " << best_smallest << std::endl;
}
