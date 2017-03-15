/*
 * pe33.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE33_HPP_
#define PE33_HPP_

#include "pe.hpp"


class pe33 : public pe
{
public:
    pe33() :
        name_("pe33")
    {};
    virtual ~pe33()
    {
    };
    virtual std::string& name();
    virtual int number() { return 33; }
    virtual void run();
private:
    std::string name_;
};

#endif /* PE33_HPP_ */
