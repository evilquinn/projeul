/*
 * pe75.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE75_HPP_
#define PE75_HPP_

#include "pe.hpp"

class pe75 : public pe
{
public:
    pe75() : name_( "pe75" ){};
    ~pe75() override = default;
    std::string& name() override;
    int          number() override { return 75; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE75_HPP_ */
