/*
 * pe59.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE59_HPP_
#define PE59_HPP_

#include "pe.hpp"

class pe59 : public pe
{
public:
    pe59() :
        name_("pe59")
    {};
    virtual ~pe59()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE59_HPP_ */
