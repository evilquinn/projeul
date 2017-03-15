/*
 * pe29.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE29_HPP_
#define PE29_HPP_

#include "pe.hpp"
#include <prime_sieve.hpp>


class pe29 : public pe
{
public:
    pe29() :
        name_("pe29")
    {};
    virtual ~pe29() {};
    virtual std::string& name();
    virtual int number() { return 29; }
    virtual void run();
private:
    std::string name_;
};

#endif /* PE29_HPP_ */
