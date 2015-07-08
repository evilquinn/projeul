/*
 * pe43.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE43_HPP_
#define PE43_HPP_

#include "pe.hpp"


class pe43 : public pe
{
public:
    pe43() :
        name_("pe43")
    {};
    virtual ~pe43()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE43_HPP_ */
