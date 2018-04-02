/*
 * pe65.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE65_HPP_
#define PE65_HPP_

#include "pe.hpp"

class pe65 : public pe
{
public:
    pe65() : name_( "pe65" ){};
    std::string& name() override;
    int          number() override { return 65; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE65_HPP_ */
