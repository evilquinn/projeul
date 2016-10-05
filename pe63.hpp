/*
 * pe63.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE63_HPP_
#define PE63_HPP_

#include "pe.hpp"


class pe63 : public pe
{
public:
    pe63() :
        name_("pe63")
    {};
    virtual ~pe63()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE63_HPP_ */
