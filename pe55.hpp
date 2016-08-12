/*
 * pe55.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE55_HPP_
#define PE55_HPP_

#include "pe.hpp"

class pe55 : public pe
{
public:
    pe55() :
        name_("pe55")
    {};
    virtual ~pe55()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE55_HPP_ */
