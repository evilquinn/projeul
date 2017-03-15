/*
 * pe36.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE36_HPP_
#define PE36_HPP_

#include "pe.hpp"


class pe36 : public pe
{
public:
    pe36() :
        name_("pe36")
    {};
    virtual ~pe36()
    {
    };
    virtual std::string& name();
    virtual int number() { return 36; }
    virtual void run();
private:
    std::string name_;
};

#endif /* PE36_HPP_ */
