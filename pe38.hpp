/*
 * pe38.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE38_HPP_
#define PE38_HPP_

#include "pe.hpp"


class pe38 : public pe
{
public:
    pe38() :
        name_("pe38")
    {};
    virtual ~pe38()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE38_HPP_ */
