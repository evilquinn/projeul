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
    ~pe54() override = default;
    std::string& name() override;
    int          number() override { return 54; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE54_HPP_ */
