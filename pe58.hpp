/*
 * pe58.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE58_HPP_
#define PE58_HPP_

#include "pe.hpp"

class pe58 : public pe
{
public:
    pe58() :
        name_("pe58")
    {};
    virtual ~pe58()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE58_HPP_ */
