/*
 * pe66.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE66_HPP_
#define PE66_HPP_

#include "pe.hpp"

class pe66 : public pe
{
public:
    pe66() : name_( "pe66" ){};
    virtual ~pe66(){};
    virtual std::string& name() { return name_; };
    virtual int          number() { return 66; }
    virtual void         run();

private:
    std::string name_;
};

#endif /* PE66_HPP_ */
