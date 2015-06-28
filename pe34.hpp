/*
 * pe34.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE34_HPP_
#define PE34_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"


class pe34 : public pe
{
public:
    pe34() :
        name_("pe34")
    {};
    virtual ~pe34()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE34_HPP_ */
