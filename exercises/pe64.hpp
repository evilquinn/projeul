/*
 * pe64.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE64_HPP_
#define PE64_HPP_

#include "pe.hpp"

class pe64 : public pe
{
public:
    pe64() : name_( "pe64" ){};
    virtual ~pe64(){};
    virtual std::string& name();
    virtual int          number() { return 64; }
    virtual void         run();

private:
    std::string name_;
};

#endif /* PE64_HPP_ */
