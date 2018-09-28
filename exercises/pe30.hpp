/*
 * pe30.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE30_HPP_
#define PE30_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

class pe30 : public pe
{
public:
    pe30() : name_( "pe30" ){};
    ~pe30() override = default;
    std::string& name() override;
    int number() override { return 30; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE30_HPP_ */
