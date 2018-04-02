/*
 * pe49.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE49_HPP_
#define PE49_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"

#define PE49_MAX_PRIMES 10000

class pe49 : public pe
{
public:
    pe49() : primes_(), name_( "pe49" ){};
    ~pe49() override = default;
    std::string& name() override;
    int          number() override { return 49; }
    void         run() override;

private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE49_HPP_ */
