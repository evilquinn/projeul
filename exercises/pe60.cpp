/*
 * pe60.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe60.hpp"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <gint.hpp>
#include <iostream>
#include <utils.hpp>

std::string& pe60::name() { return name_; }
void pe60::run()
{
    /*
     * The primes 3, 7, 109, and 673, are quite remarkable. By taking any two
     * primes and concatenating them in any order the result will always be
     * prime. For example, taking 7 and 109, both 7109 and 1097 are prime.
     * The sum of these four primes, 792, represents the lowest sum for a
     * set of four primes with this property.
     *
     * Find the lowest sum for a set of five primes for which any two primes
     * concatenate to produce another prime.
     *
     *
     */

    primes_              = prime_sieve( PE60_MAX_PRIME );
    size_t limit         = 9000;
    size_t running_total = 0;
    auto smallest_sum    = static_cast<size_t>( -1 );
    bool break_all       = false;

    std::cout << name() << std::endl;
    for ( size_t a = primes_.next_prime( 2 ); a < limit;
          a        = primes_.next_prime( a ) )
    {
        running_total += a;
        for ( size_t b = primes_.next_prime( a );
              b < limit && running_total < smallest_sum;
              b = primes_.next_prime( b ) )
        {
            if ( !primes_.is_prime( concat( a, b ) ) ||
                 !primes_.is_prime( concat( b, a ) ) )
            {
                continue;
            }
            running_total += b;
            for ( size_t c = primes_.next_prime( b );
                  c < limit && running_total < smallest_sum;
                  c = primes_.next_prime( c ) )
            {
                if ( !primes_.is_prime( concat( a, c ) ) ||
                     !primes_.is_prime( concat( c, a ) ) ||
                     !primes_.is_prime( concat( b, c ) ) ||
                     !primes_.is_prime( concat( c, b ) ) )
                {
                    continue;
                }
                running_total += c;
                for ( size_t d = primes_.next_prime( c );
                      d < limit && running_total < smallest_sum;
                      d = primes_.next_prime( d ) )
                {
                    if ( !primes_.is_prime( concat( a, d ) ) ||
                         !primes_.is_prime( concat( d, a ) ) ||
                         !primes_.is_prime( concat( b, d ) ) ||
                         !primes_.is_prime( concat( d, b ) ) ||
                         !primes_.is_prime( concat( c, d ) ) ||
                         !primes_.is_prime( concat( d, c ) ) )
                    {
                        continue;
                    }
                    running_total += d;
                    for ( size_t e = primes_.next_prime( d );
                          e < limit && running_total < smallest_sum;
                          e = primes_.next_prime( e ) )
                    {
                        if ( !primes_.is_prime( concat( a, e ) ) ||
                             !primes_.is_prime( concat( e, a ) ) ||
                             !primes_.is_prime( concat( b, e ) ) ||
                             !primes_.is_prime( concat( e, b ) ) ||
                             !primes_.is_prime( concat( c, e ) ) ||
                             !primes_.is_prime( concat( e, c ) ) ||
                             !primes_.is_prime( concat( d, e ) ) ||
                             !primes_.is_prime( concat( e, d ) ) )
                        {
                            continue;
                        }
                        running_total += e;
                        if ( running_total < smallest_sum )
                        {
                            std::cout
                                << "found new smallest: " << running_total
                                << " < " << smallest_sum << "\nfrom: " << a
                                << " " << b << " " << c << " " << d << " "
                                << e << std::endl;
                            smallest_sum = running_total;
                            if ( smallest_sum < limit )
                            {
                                break_all = true;
                                break;
                            }
                        }
                        if ( break_all )
                        {
                            break;
                        }
                        running_total -= e;
                    }
                    if ( break_all )
                    {
                        break;
                    }
                    running_total -= d;
                }
                if ( break_all )
                {
                    break;
                }
                running_total -= c;
            }
            if ( break_all )
            {
                break;
            }
            running_total -= b;
        }
        if ( break_all )
        {
            break;
        }
        running_total -= a;
    }
}
