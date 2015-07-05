/*
 * pe42.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE42_HPP_
#define PE42_HPP_

#include "pe.hpp"


class pe42 : public pe
{
public:
    pe42() :
        name_("pe42")
    {};
    virtual ~pe42()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE42_HPP_ */
