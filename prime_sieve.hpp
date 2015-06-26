/*
 * primesieve.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef PRIME_SIEVE_HPP_
#define PRIME_SIEVE_HPP_

class prime_sieve
{
public:
    prime_sieve(int max);
    virtual ~prime_sieve();

    void print();
    bool is_prime(int n);

private:
    void calc_primes();

    int   limit_;
    bool* sieve_;
};

#endif /* PRIME_SIEVE_HPP_ */
