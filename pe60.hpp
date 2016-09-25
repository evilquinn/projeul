/*
 * pe60.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE60_HPP_
#define PE60_HPP_

#include "pe.hpp"
#include <prime_sieve.hpp>

#define PE60_MAX_PRIME 20000000

class pe60 : public pe
{
public:
    pe60() :
        name_("pe60"),
        primes_(PE60_MAX_PRIME)
    {};
    virtual ~pe60()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
    prime_sieve primes_;
};

#endif /* PE60_HPP_ */
