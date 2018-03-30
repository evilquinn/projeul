/*
 * pe52.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE52_HPP_
#define PE52_HPP_

#include "pe.hpp"

class pe52 : public pe
{
public:
    pe52() : name_( "pe52" ){};
    virtual ~pe52(){};
    virtual std::string& name();
    virtual void         run();
    virtual int          number() { return 52; }
private:
    std::string name_;
};

#endif /* PE52_HPP_ */
