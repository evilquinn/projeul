/*
 * pe60.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe60.hpp"
#include <iostream>
#include <fstream>
#include <utils.hpp>
#include <gint.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

std::string& pe60::name()
{
    return name_;
}

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

    size_t limit = 30000;
    size_t running_total = 0;
    size_t smallest_sum = static_cast<size_t>(-1);

    for ( size_t a = primes_.next_prime(2);
          a < limit;
          a = primes_.next_prime(a) )
    {
        running_total += a;
        for ( size_t b = primes_.next_prime(a);
              b < limit && running_total < smallest_sum;
              b = primes_.next_prime(b) )
        {
            if ( ! is_prime(primes_, concat(a, b)) ||
                 ! is_prime(primes_, concat(b, a)) )
            {
                continue;
            }
            running_total += b;
            for ( size_t c = primes_.next_prime(b);
                  c < limit && running_total < smallest_sum;
                  c = primes_.next_prime(c) )
            {
                if ( ! is_prime(primes_, concat(a, c)) ||
                     ! is_prime(primes_, concat(c, a)) ||
                     ! is_prime(primes_, concat(b, c)) ||
                     ! is_prime(primes_, concat(c, b)) )
                {
                    continue;
                }
                running_total += c;
                for ( size_t d = primes_.next_prime(c);
                      d < limit && running_total < smallest_sum;
                      d = primes_.next_prime(d) )
                {
                    if ( ! is_prime(primes_, concat(a, d)) ||
                         ! is_prime(primes_, concat(d, a)) ||
                         ! is_prime(primes_, concat(b, d)) ||
                         ! is_prime(primes_, concat(d, b)) ||
                         ! is_prime(primes_, concat(c, d)) ||
                         ! is_prime(primes_, concat(d, c)) )
                    {
                        continue;
                    }
                    running_total += d;
                    for ( size_t e = primes_.next_prime(d);
                          e < limit && running_total < smallest_sum;
                          e = primes_.next_prime(e) )
                    {
                        if ( ! is_prime(primes_, concat(a, e)) ||
                             ! is_prime(primes_, concat(e, a)) ||
                             ! is_prime(primes_, concat(b, e)) ||
                             ! is_prime(primes_, concat(e, b)) ||
                             ! is_prime(primes_, concat(c, e)) ||
                             ! is_prime(primes_, concat(e, c)) ||
                             ! is_prime(primes_, concat(d, e)) ||
                             ! is_prime(primes_, concat(e, d)) )
                        {
                            continue;
                        }
                        running_total += e;
                        if ( running_total < smallest_sum )
                        {
                            std::cout << "found new smallest: "
                                      << running_total << " < " << smallest_sum
                                      << "\nfrom: "
                                      << a << " " << b << " " << c << " "
                                      << d << " " << e
                                      << std::endl;
                            smallest_sum = running_total;
                        }
                        running_total -= e;
                    }
                    running_total -= d;
                }
                running_total -= c;
            }
            running_total -= b;
        }
        running_total -= a;
    }
}
