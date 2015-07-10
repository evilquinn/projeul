/*
 * pe44.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE44_HPP_
#define PE44_HPP_

#include "pe.hpp"
#include "pentagonal_numbers/pentagonal_numbers.hpp"

#define PE44_NUM_PENTS 1000000

class pe44 : public pe
{
public:
    pe44() :
        pents_(PE44_NUM_PENTS),
        name_("pe44")
    {};
    virtual ~pe44()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    pentagonal_numbers pents_;
    std::string name_;
};

#endif /* PE44_HPP_ */
