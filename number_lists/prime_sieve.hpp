/*
 * primesieve.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef PRIME_SIEVE_HPP_
#define PRIME_SIEVE_HPP_

#include <stddef.h>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <deque>

#define PRIME_SIEVE_MAX_PRIME 67000000

class prime_sieve
{
public:
    prime_sieve() : limit_( 0 ), sieve_( 0 ){};
    explicit prime_sieve( size_t limit );
    virtual ~prime_sieve();

    void print();
    size_t limit();
    bool is_prime( size_t n );
    size_t shit_next_prime( size_t from );
    size_t next_prime( size_t from );
    size_t prev_prime( size_t from );
    size_t sum_range( size_t lower, size_t upper, size_t& num_in_range );
    size_t shit_sum_range( size_t lower,
                           size_t upper,
                           std::deque<size_t>& sumees );
    size_t num_in_range( size_t lower, size_t upper );

private:
    enum find_direction
    {
        PREV,
        NEXT
    };
    size_t prev_or_next( size_t from, enum find_direction direction );
    void calc_primes();

    size_t limit_;
    boost::dynamic_bitset<> sieve_;
};

#endif /* PRIME_SIEVE_HPP_ */
