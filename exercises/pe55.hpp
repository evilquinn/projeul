/*
 * pe55.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE55_HPP_
#define PE55_HPP_

#include "pe.hpp"

class pe55 : public pe
{
public:
    pe55() : name_( "pe55" ){};
    ~pe55() override = default;
    std::string& name() override;
    int          number() override { return 55; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE55_HPP_ */
