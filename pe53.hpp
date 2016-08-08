/*
 * pe53.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE53_HPP_
#define PE53_HPP_

#include "pe.hpp"

class pe53 : public pe
{
public:
    pe53() :
        name_("pe53")
    {};
    virtual ~pe53()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE53_HPP_ */
