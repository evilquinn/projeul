/*
 * pe40.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE40_HPP_
#define PE40_HPP_

#include "pe.hpp"

class pe40 : public pe
{
public:
    pe40() : name_( "pe40" ){};
    ~pe40() override = default;
    std::string& name() override;
    int          number() override { return 40; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE40_HPP_ */
