/*
 * pe.hpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE_HPP_
#define PE_HPP_

#include <string>

class pe
{
public:
    virtual ~pe(){};
    // abstract, returns name of exercise
    virtual std::string& name()   = 0;
    virtual void         run()    = 0;
    virtual int          number() = 0;
};

#endif /* PE_HPP_ */
