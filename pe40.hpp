/*
 * pe40.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE40_HPP_
#define PE40_HPP_

#include "pe.hpp"


class pe40 : public pe
{
public:
    pe40() :
        name_("pe40")
    {};
    virtual ~pe40()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE40_HPP_ */
