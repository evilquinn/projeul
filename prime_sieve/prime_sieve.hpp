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

#define PRIME_SIEVE_MAX_PRIME 67000000

class prime_sieve
{
public:
    prime_sieve(size_t max);
    virtual ~prime_sieve();

    void print();
    bool is_prime(size_t n);

private:
    void calc_primes();

    size_t                  limit_;
    boost::dynamic_bitset<> sieve_;
};

#endif /* PRIME_SIEVE_HPP_ */
