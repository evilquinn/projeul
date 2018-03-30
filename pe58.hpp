/*
 * pe58.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE58_HPP_
#define PE58_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

#define PE58_MAX_PRIME 30000

class pe58 : public pe
{
public:
    pe58() : name_( "pe58" ), primes_(){};
    virtual ~pe58(){};
    virtual std::string& name();
    virtual int          number() { return 58; }
    virtual void         run();

private:
    std::string name_;
    prime_sieve primes_;
};

#endif /* PE58_HPP_ */
