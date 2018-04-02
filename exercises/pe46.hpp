/*
 * pe46.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE46_HPP_
#define PE46_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

#define PE46_NUM_PRIMES 100000

class pe46 : public pe
{
public:
    pe46() : primes_(), squares_(), name_( "pe46" ){};
    ~pe46() override = default;
    std::string& name() override;
    int          number() override { return 46; }
    void         run() override;
    bool fulfills_goldbachs_conjecture( size_t i );

private:
    prime_sieve         primes_;
    std::vector<size_t> squares_;
    std::string         name_;
};

#endif /* PE46_HPP_ */
