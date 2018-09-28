/*
 * pe76.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE76_HPP_
#define PE76_HPP_

#include "pe.hpp"

class pe76 : public pe
{
public:
    pe76() : name_( "pe76" ){};
    ~pe76() override = default;
    std::string& name() override;
    int number() override { return 76; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE76_HPP_ */
