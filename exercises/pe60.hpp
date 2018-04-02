/*
 * pe60.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE60_HPP_
#define PE60_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

#define PE60_MAX_PRIME 100000000

class pe60 : public pe
{
public:
    pe60() : name_( "pe60" ), primes_(){};
    ~pe60() override = default;
    std::string& name() override;
    int          number() override { return 60; }
    void         run() override;

private:
    std::string name_;
    prime_sieve primes_;
};

#endif /* PE60_HPP_ */
