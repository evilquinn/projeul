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
    virtual ~pe30(){};
    virtual std::string& name();
    virtual int          number() { return 30; }
    virtual void         run();

private:
    std::string name_;
};

#endif /* PE30_HPP_ */
