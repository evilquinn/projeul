/*
 * pe35.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE35_HPP_
#define PE35_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"


class pe35 : public pe
{
public:
    pe35() :
        primes_(1000000),
        name_("pe35")
    {};
    virtual ~pe35()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE35_HPP */
