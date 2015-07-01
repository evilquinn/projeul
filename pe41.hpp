/*
 * pe41.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE41_HPP_
#define PE41_HPP_

#include "pe.hpp"
#include "prime_sieve.hpp"


class pe41 : public pe
{
public:
    pe41() :
        name_("pe41")
    {};
    virtual ~pe41()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE41_HPP_ */
