/*
 * pe64.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE64_HPP_
#define PE64_HPP_

#include "pe.hpp"

class pe64 : public pe
{
public:
    pe64() : name_( "pe64" ){};
    ~pe64() override = default;
    std::string& name() override;
    int number() override { return 64; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE64_HPP_ */
