/*
 * pe39.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE39_HPP_
#define PE39_HPP_

#include "pe.hpp"
#include "prime_sieve/prime_sieve.hpp"


class pe39 : public pe
{
public:
    pe39() :
        name_("pe39")
    {};
    virtual ~pe39()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE39_HPP_ */
