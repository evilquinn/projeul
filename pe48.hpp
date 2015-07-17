/*
 * pe48.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE48_HPP_
#define PE48_HPP_

#include "pe.hpp"


class pe48 : public pe
{
public:
    pe48() :
        name_("pe48")
    {};
    virtual ~pe48()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE48_HPP_ */
