/*
 * pe44.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE44_HPP_
#define PE44_HPP_

#include "pe.hpp"


class pe44 : public pe
{
public:
    pe44() :
        name_("pe44")
    {};
    virtual ~pe44()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE44_HPP_ */
