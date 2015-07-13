/*
 * pe46.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE46_HPP_
#define PE46_HPP_

#include "pe.hpp"
#include <prime_sieve.hpp>

#define PE46_NUM_PRIMES 100000

class pe46 : public pe
{
public:
    pe46() :
        primes_(PE46_NUM_PRIMES),
        squares_(PE46_NUM_PRIMES),
        name_("pe46")
    {};
    virtual ~pe46()
    {
    };
    virtual std::string& name();
    virtual void run();
    bool fulfills_goldbachs_conjecture(size_t i);
    size_t prev_prime(size_t i);
private:
    prime_sieve primes_;
    std::vector<size_t> squares_;
    std::string name_;
};

#endif /* PE46_HPP_ */
