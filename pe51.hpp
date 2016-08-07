/*
 * pe51.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE51_HPP_
#define PE51_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"

#define PE51_MAX_PRIMES 1000000

class pe51 : public pe
{
public:
    pe51() :
        primes_(PE51_MAX_PRIMES),
        name_("pe51")
    {};
    virtual ~pe51()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE51_HPP_ */
