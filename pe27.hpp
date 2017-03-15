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
        primes_(NULL),
        name_("pe27")
    {};
    virtual ~pe27()
    {
        delete primes_;
    };
    virtual std::string& name();
    virtual int number() { return 27; }
    virtual void run();
private:
    prime_sieve* primes_;
    std::string name_;
};

#endif /* PE27_HPP_ */
