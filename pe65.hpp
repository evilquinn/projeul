/*
 * pe65.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE65_HPP_
#define PE65_HPP_

#include "pe.hpp"


class pe65 : public pe
{
public:
    pe65() :
        name_("pe65")
    {};
    virtual ~pe65()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE65_HPP_ */
