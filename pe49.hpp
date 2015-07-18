/*
 * pe49.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE49_HPP_
#define PE49_HPP_

#include "pe.hpp"


class pe49 : public pe
{
public:
    pe49() :
        name_("pe49")
    {};
    virtual ~pe49()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE49_HPP_ */
