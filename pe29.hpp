/*
 * pe29.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE29_HPP_
#define PE29_HPP_

#include "pe.hpp"
#include "prime_sieve/prime_sieve.hpp"


class pe29 : public pe
{
public:
    pe29() :
        primes_(new prime_sieve(1000000)),
        name_("pe29")
    {};
    virtual ~pe29()
    {
        delete primes_;
    };
    virtual std::string& name();
    virtual void run();
private:
    prime_sieve* primes_;
    std::string name_;
};

#endif /* PE29_HPP_ */
