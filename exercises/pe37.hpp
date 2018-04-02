/*
 * pe37.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE37_HPP_
#define PE37_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

class pe37 : public pe
{
public:
    pe37() : primes_(), name_( "pe37" ){};
    ~pe37() override = default;
    std::string& name() override;
    int          number() override { return 37; }
    void         run() override;

private:
    bool is_trunc_prime_rtl( int n );
    bool is_trunc_prime_ltr( int n );
    bool is_trunc_prime( int n );

    prime_sieve primes_;
    std::string name_;
};

#endif /* PE37_HPP_ */
