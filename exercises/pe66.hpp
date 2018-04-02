/*
 * pe66.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE66_HPP_
#define PE66_HPP_

#include "pe.hpp"

class pe66 : public pe
{
public:
    pe66() : name_( "pe66" ) {}
    ~pe66() override = default;
    std::string& name() override;
    int          number() override { return 66; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE66_HPP_ */
