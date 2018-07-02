/*
 * pe74.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE74_HPP_
#define PE74_HPP_

#include "pe.hpp"

class pe74 : public pe
{
public:
    pe74() : name_( "pe74" ){};
    ~pe74() override = default;
    std::string& name() override;
    int          number() override { return 74; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE74_HPP_ */
