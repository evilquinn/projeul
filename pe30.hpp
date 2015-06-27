/*
 * pe30.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE30_HPP_
#define PE30_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"


class pe30 : public pe
{
public:
    pe30() :
        primes_(new prime_sieve(1000000)),
        name_("pe30")
    {};
    virtual ~pe30()
    {
        delete primes_;
    };
    virtual std::string& name();
    virtual void run();
private:
    prime_sieve* primes_;
    std::string name_;
};

#endif /* PE30_HPP_ */
