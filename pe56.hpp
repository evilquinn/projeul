/*
 * pe56.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE56_HPP_
#define PE56_HPP_

#include "pe.hpp"

class pe56 : public pe
{
public:
    pe56() :
        name_("pe56")
    {};
    virtual ~pe56()
    {
    };
    virtual std::string& name();
    virtual int number() { return 56; }
    virtual void run();
private:
    std::string name_;
};

#endif /* PE56_HPP_ */
