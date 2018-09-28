/*
 * pe50.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE50_HPP_
#define PE50_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"

#define PE50_MAX_PRIMES 1000000

class pe50 : public pe
{
public:
    pe50() : primes_(), name_( "pe50" ){};
    ~pe50() override = default;
    std::string& name() override;
    int number() override { return 50; }
    void run() override;

private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE50_HPP_ */
