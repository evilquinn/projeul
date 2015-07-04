/*
 * pe32.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE32_HPP_
#define PE32_HPP_

#include "pe.hpp"
#include "prime_sieve/prime_sieve.hpp"


class pe32 : public pe
{
public:
    pe32() :
        name_("pe32")
    {};
    virtual ~pe32()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE32_HPP_ */
