/*
 * pe67.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE67_HPP_
#define PE67_HPP_

#include "pe.hpp"

class pe67 : public pe
{
public:
    pe67() : name_( "pe67" ){};
    virtual ~pe67(){};
    virtual std::string& name() { return name_; };
    virtual void         run();
    virtual int          number() { return 67; };
private:
    std::string name_;
};

#endif /* PE67_HPP_ */
