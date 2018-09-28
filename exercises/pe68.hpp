/*
 * pe68.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE68_HPP_
#define PE68_HPP_

#include "pe.hpp"

class pe68 : public pe
{
public:
    pe68() : name_( "pe68" ){};
    ~pe68() override = default;
    std::string& name() override;
    int number() override { return 68; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE68_HPP_ */
