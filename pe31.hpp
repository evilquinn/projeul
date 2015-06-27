/*
 * pe31.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE31_HPP_
#define PE31_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"


class pe31 : public pe
{
public:
    pe31() :
        name_("pe31")
    {};
    virtual ~pe31()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE31_HPP_ */
