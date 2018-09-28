/*
 * pe27.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE27_HPP_
#define PE27_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

class pe27 : public pe
{
public:
    pe27() : primes_( nullptr ), name_( "pe27" ){};
    ~pe27() override { delete primes_; };
    std::string& name() override;
    int number() override { return 27; }
    void run() override;

private:
    prime_sieve* primes_;
    std::string name_;
};

#endif /* PE27_HPP_ */
