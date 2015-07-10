/*
 * pe37.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE37_HPP_
#define PE37_HPP_

#include "pe.hpp"
#include <prime_sieve.hpp>


class pe37 : public pe
{
public:
    pe37() :
        primes_(1000000),
        name_("pe37")
    {};
    virtual ~pe37()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    bool is_trunc_prime_rtl(int n);
    bool is_trunc_prime_ltr(int n);
    bool is_trunc_prime(int n);

    prime_sieve primes_;
    std::string name_;
};

#endif /* PE37_HPP_ */
