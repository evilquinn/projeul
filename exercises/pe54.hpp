/*
 * pe54.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE54_HPP_
#define PE54_HPP_

#include "pe.hpp"

class pe54 : public pe
{
public:
    pe54() : name_( "pe54" ){};
    virtual ~pe54(){};
    virtual std::string& name();
    virtual int          number() { return 54; }
    virtual void         run();

private:
    std::string name_;
};

#endif /* PE54_HPP_ */
