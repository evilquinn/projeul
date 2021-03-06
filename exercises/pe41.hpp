/*
 * pe41.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE41_HPP_
#define PE41_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

class pe41 : public pe
{
public:
    pe41() : primes_(), name_( "pe41" ){};
    ~pe41() override = default;
    std::string& name() override;
    int number() override { return 41; }
    void run() override;

private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE41_HPP_ */
