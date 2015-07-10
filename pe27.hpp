/*
 * pe27.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE27_HPP_
#define PE27_HPP_

#include "pe.hpp"
#include <prime_sieve.hpp>


class pe27 : public pe
{
public:
    pe27() :
        primes_(new prime_sieve(1000000)),
        name_("pe27")
    {};
    virtual ~pe27()
    {
        delete primes_;
    };
    virtual std::string& name();
    virtual void run();
private:
    prime_sieve* primes_;
    std::string name_;
};

#endif /* PE27_HPP_ */
