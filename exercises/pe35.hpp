/*
 * pe35.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE35_HPP_
#define PE35_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

class pe35 : public pe
{
public:
    pe35() : primes_(), name_( "pe35" ){};
    ~pe35() override = default;
    std::string& name() override;
    int number() override { return 35; }
    void run() override;

private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE35_HPP */
