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
    pe51() : primes_(), name_( "pe51" ){};
    ~pe51() override = default;
    std::string& name() override;
    int number() override { return 51; }
    void run() override;

private:
    prime_sieve primes_;
    std::string name_;
};

#endif /* PE51_HPP_ */
