/*
 * pe57.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE57_HPP_
#define PE57_HPP_

#include "pe.hpp"

class pe57 : public pe
{
public:
    pe57() :
        name_("pe57")
    {};
    virtual ~pe57()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE57_HPP_ */
