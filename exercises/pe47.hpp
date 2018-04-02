/*
 * pe47.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE47_HPP_
#define PE47_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

#define PE47_NUM_PRIMES 10000000

class pe47 : public pe
{
public:
    pe47() : primes_(), name_( "pe47" ){};
    ~pe47() override = default;
    std::string& name() override;
    int          number() override { return 47; }
    void         run() override;
    bool num_has_n_distinct_prime_factors( size_t num, size_t n );

private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE47_HPP_ */
