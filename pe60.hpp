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
    virtual ~pe60(){};
    virtual std::string& name();
    virtual int          number() { return 60; }
    virtual void         run();

private:
    std::string name_;
    prime_sieve primes_;
};

#endif /* PE60_HPP_ */
