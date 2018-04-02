/*
 * pe61.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE61_HPP_
#define PE61_HPP_

#include "pe.hpp"

class pe61 : public pe
{
public:
    pe61() : name_( "pe61" ){};
    virtual ~pe61(){};
    virtual std::string& name();
    virtual int          number() { return 61; }
    virtual void         run();

private:
    std::string name_;
};

#endif /* PE61_HPP_ */
